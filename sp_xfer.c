/*
Replacement for Fujitsu's "serial programming mode" code loaded by ROM
*/

#include "common.h"
#include "platform.h"

OSTRUCT(fm3_usb0_t, 0x78)
OFIELD(0x40, u8 UDCS);
OFIELD(0x44, u16 EP0IS);
OFIELD(0x48, u16 EP0OS);
OFIELD(0x60, u16 EP0DT);
OSTRUCT_END

volatile struct fm3_usb0_t *const usb0 =
    (struct fm3_usb0_t * const)FM3_USB0_BASE;

/*
 Communication code is ripped from Fujitsu
 since it uses state setup by ROM...
*/

#define USB0_NUM_ENDPOINTS 6

struct usb_ep0_state_t {
  void *buf_out;
  void *buf_in;
  u16 buf_out_len;
  u16 field_A;
  u8 field_C;
  u8 field_D;
  u8 field_E;
  u8 field_F;
  u8 field_10;
} __attribute__((packed));
ASSERT_STRSIZE(struct usb_ep0_state_t, 0x11);

struct usb_ep_state_t {
  u8 *buf_beg;
  u8 *buf_end;
  u8 *buf_rptr;
  u8 *buf_wptr;
  u8 field_10;
  u8 field_11;
  u8 field_12;
  u8 field_13;
  u16 len_pending;
  u8 field_16;
  u8 field_17;
  u32 buf_len;
  u16 len_max;
  u8 ep_index;
  u8 field_1F;
  u8 field_20;
  u8 mode;
  u8 field_22;
  u8 field_23;
  u8 field_24;
  u8 field_25;
  u8 field_26;
  u8 field_27;
  vu16 *EPxC;
  vu16 *EPxS;
  vu16 *EPxDT;
  u8 field_34;
  u8 _pad_35[3];
} __attribute__((packed));
ASSERT_STRSIZE(struct usb_ep_state_t, 0x38);

struct usb_ep_states_t {
  struct usb_ep0_state_t *ep0;
  struct usb_ep_state_t *epX[USB0_NUM_ENDPOINTS - 1];
};

// Defined linker script
extern struct usb_ep_states_t usb0_ep_states;

static struct usb_ep0_state_t *get_usb0_ep0_state() {
  return usb0_ep_states.ep0;
}

static struct usb_ep_state_t *get_usb0_epX_state(int ep_idx) {
  return usb0_ep_states.epX[ep_idx - 1];
}

static int usb0_clear_interrupts() {
  int bus_reset = 0;
  if (!usb0->UDCS)
    return 0;
  if (usb0->UDCS & 1)
    usb0->UDCS &= ~1;
  if (usb0->UDCS & 0x20)
    usb0->UDCS &= ~0x20;
  if (usb0->UDCS & 4)
    usb0->UDCS &= ~4;
  if (usb0->UDCS & 8) {
    bus_reset = 1;
    usb0->UDCS &= ~8;
  }
  if (usb0->UDCS & 0x10)
    usb0->UDCS &= ~0x10;
  return bus_reset;
}

static void usb0_ep0_xfer(struct usb_ep0_state_t *ep0) {
  u16 *buf;
  u32 len;

  if (usb0->EP0OS & 0x400) {
    if (!(usb0->UDCS & 2)) {
      len = usb0->EP0OS & 0x3F;
      if (len) {
        buf = ep0->buf_in;
        while (len >= 2) {
          *buf++ = usb0->EP0DT;
          len -= 2;
        }
        if (len)
          *(u8 *)buf = usb0->EP0DT;
        ep0->buf_out_len = 0;
        usb0->EP0IS |= 0x4000;
      }
      usb0->EP0OS &= ~0x400;
    }
    if (ep0->buf_out_len) {
      while (!(usb0->EP0IS & 0x400))
        ;
      buf = ep0->buf_out;
      for (len = ep0->buf_out_len; len >= 2; len -= 2) {
        usb0->EP0DT = *buf++;
      }
      if (len)
        *(u8 *)&usb0->EP0DT = *(u8 *)buf;
      ep0->buf_out_len = 0;
      usb0->EP0IS |= 0x4000;
    }
  }
}

static void usb0_epX_read(struct usb_ep_state_t *ep) {
  int len;
  u8 *pDT;
  u32 space_avail;
  int pos;

  len = 0;
  pDT = (u8 *)ep->EPxDT;

  if (ep->mode == 1) {
    return;
  }

  if (ep->mode == 2) {
    if (ep->buf_rptr < ep->buf_wptr) {
      space_avail = (u32)ep->buf_rptr + ep->buf_len - (u32)ep->buf_wptr;
    } else {
      space_avail = ep->buf_rptr - ep->buf_wptr;
      if (space_avail == 0)
        space_avail = ep->buf_len;
    }
    len = space_avail - 1;
    // checkout EPxS.SIZEx
    if (len >= *(u8 *)ep->EPxS) {
      if (len > *(u8 *)ep->EPxS)
        len = *(u8 *)ep->EPxS;
      ep->len_pending = len;
      pos = 0;
      while (len >= 1) {
        *ep->buf_wptr++ = pDT[pos & 1];
        if (ep->buf_wptr > ep->buf_end)
          ep->buf_wptr = ep->buf_beg;
        --len;
        ++pos;
      }
    }
  }

  if (len) {
    *ep->EPxS &= ~0x4000;
    // dword_20003008 = ep;
  } else {
    *ep->EPxS &= ~0x0400;
  }
}

static int usb_sync_buffers() {
  int bus_reset = usb0_clear_interrupts();
  if (!bus_reset) {
    int ep_idx;
    usb0_ep0_xfer(get_usb0_ep0_state());
    for (ep_idx = 1; ep_idx < USB0_NUM_ENDPOINTS; ++ep_idx) {
      struct usb_ep_state_t *ep;
      ep = get_usb0_epX_state(ep_idx);
      if (ep->field_22 == 3) {
        if ((*ep->EPxS & 0x8200) == 0x200)
          *ep->EPxS &= ~0x200;
        if (*ep->EPxS & 0x400) {
          if (ep_idx == 2) {
            *ep->EPxS &= ~0x400;
            if (ep->len_pending)
              ep->len_pending = 0;
          } else if (ep_idx == 3) {
            *ep->EPxS &= ~0x400;
          } else {
            usb0_epX_read(ep);
          }
        }
      }
    }
  }
  return bus_reset;
}

static u32 usb_read(struct usb_ep_state_t *ep, u8 *buf, u32 len) {
  u8 *rptr;
  u32 num_read;

  if (!ep->field_34)
    return 0;
  if (ep->mode != 2)
    return 0;
  rptr = ep->buf_rptr;
  for (num_read = 0; num_read < len && rptr != ep->buf_wptr; ++num_read) {
    *buf++ = *rptr++;
    if (rptr > ep->buf_end)
      rptr = ep->buf_beg;
  }
  ep->buf_rptr = rptr;
  return num_read;
}

static u32 usb_write(struct usb_ep_state_t *ep, u8 *buf, u32 len) {
  u8 *pDT;
  u32 num_written;
  u32 pos;

  if (ep->len_pending)
    return 0;
  if (!(*ep->EPxS & 0x400))
    return 0;
  pDT = (u8 *)ep->EPxDT;
  if (len >= ep->len_max)
    len = ep->len_max;
  num_written = len;
  pos = 0;
  while (len >= 1) {
    pDT[pos & 1] = *buf++;
    --len;
    ++pos;
  }
  ep->len_pending = num_written;
  return num_written;
}

static int usb_xfer(u8 *buf, u16 len, int is_write) {
  u32 rem;
  u32 num_xfer;

  for (rem = len;; rem -= num_xfer) {
    usb_sync_buffers();
    num_xfer = is_write ? usb_write(get_usb0_epX_state(2), buf, rem)
                        : usb_read(get_usb0_epX_state(1), buf, rem);
    if (num_xfer >= rem)
      break;
    buf += num_xfer;
  }
  usb_sync_buffers();
  return 0;
}

void sp_read(u8 *buf, u16 len) { usb_xfer(buf, len, 0); }
void sp_write(u8 *buf, u16 len) { usb_xfer(buf, len, 1); }

__attribute__((section(".init"))) void sram_entry() {
  // Ack the "finalize" cmd
  // Fujitsu's code sends 0x31 here
  u8 alive = 0xA1;
  sp_write(&alive, sizeof(alive));

  // do the real stuff
  extern void serv_main();
  serv_main();
}
