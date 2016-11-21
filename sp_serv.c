#include "common.h"
#include "sp_xfer.h"

#define SP_READ(x)                                                             \
  do {                                                                         \
    sp_read((void *)&(x), sizeof(x));                                          \
  } while (0)

#define SP_WRITE(x)                                                            \
  do {                                                                         \
    sp_write((void *)&(x), sizeof(x));                                         \
  } while (0)

#define CMD_PING 0x18
#define CMD_READ 0x20
#define CMD_READV 0x21
#define CMD_WRITEV 0x22
#define CMD_EXEC 0x23
#define CMD_WRITE 0x00

#define STATUS_OK 1
#define STATUS_NG 2
#define STATUS_UNK_CMD 4

// in order to keep python side simple...annoyingly
// have to keep using Fujitsu's struct
struct rw_args_t {
  u8 *addr;
  u16 unused;
  u16 len;
} __attribute__((packed));

static void send_ack(u8 cmd, u8 status) {
  u8 ack = (cmd & 0xf0) | status;
  SP_WRITE(ack);
}

static void do_rw(u8 cmd) {
  struct rw_args_t args;
  u8 checksum;
  SP_READ(args);
  args.addr = (u8 *)__builtin_bswap32((u32)args.addr);
  args.len = __builtin_bswap16(args.len);

  // note: not fully compatible with Fujitsu sram code,
  // but should be compatible with ROM
  switch (cmd) {
  case CMD_READ:
    SP_READ(checksum);
    sp_write(args.addr, args.len);
    break;
  case CMD_WRITE:
    sp_read(args.addr, args.len);
    SP_READ(checksum);
    break;
  }
  send_ack(cmd, STATUS_OK);
}

struct rw_v_args_t {
  void *addr;
  u8 size;
} __attribute__((packed));

static void do_rw_v(u8 cmd) {
  struct rw_v_args_t args;
  SP_READ(args);
  switch (cmd) {
  case CMD_READV:
    switch (args.size) {
    case sizeof(u8): {
      u8 val = *(vu8 *)args.addr;
      SP_WRITE(val);
    } break;
    case sizeof(u16): {
      u16 val = *(vu16 *)args.addr;
      SP_WRITE(val);
    } break;
    case sizeof(u32): {
      u32 val = *(vu32 *)args.addr;
      SP_WRITE(val);
    } break;
    }
    break;
  case CMD_WRITEV:
    switch (args.size) {
    case sizeof(u8): {
      u8 val;
      SP_READ(val);
      *(vu8 *)args.addr = val;
    } break;
    case sizeof(u16): {
      u16 val;
      SP_READ(val);
      *(vu16 *)args.addr = val;
    } break;
    case sizeof(u32): {
      u32 val;
      SP_READ(val);
      *(vu32 *)args.addr = val;
    } break;
    }
    break;
  }
  send_ack(cmd, STATUS_OK);
}

static void do_exec() {
  void *addr;
  SP_READ(addr);
  typedef void (*just_jump_t)(void);
  ((just_jump_t)addr)();
}

void serv_main() {
  while (1) {
    u8 cmd;
    SP_READ(cmd);
    switch (cmd) {
    case CMD_PING:
      send_ack(cmd, STATUS_OK);
      break;
    case CMD_READ:
    case CMD_WRITE:
      do_rw(cmd);
      break;
    case CMD_READV:
    case CMD_WRITEV:
      do_rw_v(cmd);
      break;
    case CMD_EXEC:
      do_exec();
      break;
    default:
      send_ack(cmd, STATUS_UNK_CMD);
      break;
    }
  }
}
