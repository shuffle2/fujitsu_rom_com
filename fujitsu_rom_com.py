import sys
import struct
import code
import serial
import binascii
import argparse


def fmt_from_size(size):
    if size == 1:
        return 'B'
    if size == 2:
        return 'H'
    if size == 4:
        return 'L'
    return None


class RomCom:
    # loaded code may optionally reconfigure this
    # fujitsu's provided code switches to 115200 for example
    BR_ROM = 9600
    BR_SRAM = 115200
    CMD_WRITE = 0
    CMD_PING = 0x18
    CMD_READ = 0x20
    CMD_READV = 0x21
    CMD_WRITEV = 0x22
    CMD_FINALIZE = 0xc0
    STATUS_OK = 1
    STATUS_NG = 2
    STATUS_UNK_CMD = 4
    # for usb, rom hardcodes where it jumps to
    # for uart, jump target is last addr passed to CMD_WRITE
    USB_CODE_ENTRY = 0x20000000

    def _open_dev(s, path, baud_rate):
        s.path = path
        s.dev = serial.Serial(s.path, s.BR_ROM, timeout=1)

    def __init__(s, path, debug=False):
        s._open_dev(path, s.BR_ROM)
        s.dbg = debug

    def reopen_dev(s):
        # seems to work, so why not!
        # perhaps the USBVCOM driver is just lying to us...
        s.dev.close()
        s._open_dev(s.path, s.BR_SRAM)

    def print(s, *args):
        if s.dbg:
            print(*args)

    def _checksum(s, buf):
        return struct.pack('>B', sum(buf) & 0xff)

    def _send(s, buf):
        s.print('write: %s' % (binascii.hexlify(buf)))
        s.dev.write(buf)

    def recv_u8(s):
        d = struct.unpack('>B', s.dev.read(1))[0]
        s.print('read: %02x' % (d))
        return d

    def _cmd_with_checksum(s, cmd, buf):
        d = struct.pack('>B', cmd) + buf
        s._send(d + s._checksum(d))

    def _check_rv(s, cmd, check_cmd=True):
        rv = s.recv_u8()
        s.print('cmd %02x rv %02x' % (cmd, rv))
        if check_cmd and (rv & 0xf0) != (cmd & 0xf0):
            print('rv for wrong cmd')
            return False
        status = rv & 0xf
        if status == s.STATUS_OK:
            return True
        elif status == s.STATUS_NG:
            return False
        elif status == s.STATUS_UNK_CMD:
            print('unknown cmd')
            return False
        else:
            print('unknown status')
            return False

    def ping(s):
        d = struct.pack('>B', s.CMD_PING)
        s._send(d)
        return s._check_rv(s.CMD_PING)

    def try_ping(s):
        try:
            return s.ping()
        except:
            return False

    def read(s, addr, size):
        d = struct.pack('>LHH', addr, 0, size)
        s._cmd_with_checksum(s.CMD_READ, d)
        d = s.dev.read(size)
        if not s._check_rv(s.CMD_READ):
            return b''
        return d

    def write(s, addr, buf):
        d = struct.pack('>LHH', addr, 0, len(buf)) + buf
        s._cmd_with_checksum(s.CMD_WRITE, d)
        return s._check_rv(s.CMD_WRITE)

    def finalize(s):
        # contents of this buffer are not actually used but
        # it must still have correct checksum
        d = b'\0' * 8
        s._cmd_with_checksum(s.CMD_FINALIZE, d)
        # the return value comes from rom OR loaded code
        # rom returns 0xc2 if it fails, but fujitsu's loaded code
        # will return 0x31, which would normally be considered
        # a response for the wrong cmd...
        return s._check_rv(s.CMD_FINALIZE, False)

    def exec_file(s, path):
        try:
            with open(path, 'rb') as f:
                if not s.write(s.USB_CODE_ENTRY, f.read()):
                    return False
            if not s.ping():
                return False
            if not s.finalize():
                return False
        except:
            return False
        return True

    def _read_v(s, addr, type_len):
        d = struct.pack('<BLB', s.CMD_READV, addr, type_len)
        s._send(d)
        d = s.dev.read(type_len)
        assert s._check_rv(s.CMD_READV)

        return struct.unpack('<' + fmt_from_size(type_len), d)[0]

    def read8(s, addr): return s._read_v(addr, 1)

    def read16(s, addr): return s._read_v(addr, 2)

    def read32(s, addr): return s._read_v(addr, 4)

    def _write_v(s, addr, type_len, val):
        d = struct.pack('<BLB' + fmt_from_size(type_len),
                        s.CMD_WRITEV, addr, type_len, val)
        s._send(d)
        return s._check_rv(s.CMD_WRITEV)

    def write8(s, addr, val): return s._write_v(addr, 1, val)

    def write16(s, addr, val): return s._write_v(addr, 2, val)

    def write32(s, addr, val): return s._write_v(addr, 4, val)


def com_open(serial_path, debug):
    try:
        c = RomCom(serial_path, debug)
        if not c.try_ping():
            print('failed to ping, make sure rom is in serial programming mode')
            return None
        return c
    except:
        print('failed to open %s' % (serial_path))
        return None

if __name__ == '__main__':
    parser = argparse.ArgumentParser('Fujitsu Cortex-M3/M4 ROM comms')
    parser.add_argument('--port', default='COM4')
    parser.add_argument('--exec_file', default='./sram_code.bin')
    parser.add_argument('--skip_load', action='store_true')
    parser.add_argument('--debug', action='store_true')
    args = parser.parse_args()

    c = com_open(args.port, args.debug)
    if c is None:
        exit()

    if not args.skip_load:
        rv = c.exec_file(args.exec_file)
        print('file exec %s' % ('OK' if rv else 'NG'))

    c.reopen_dev()

    # do the reg pokes non-sp mode boot does...
    FM3_GPIO_BASE = 0x40033000
    GPIO_ADE = FM3_GPIO_BASE + 0x500
    GPIO_EPFR00 = FM3_GPIO_BASE + 0x600
    GPIO_PFR0 = FM3_GPIO_BASE + 0
    GPIO_PCR0 = FM3_GPIO_BASE + 0x100
    GPIO_PDIR0 = FM3_GPIO_BASE + 0x300
    c.write32(GPIO_ADE, 0)
    c.write32(GPIO_EPFR00, 0)
    c.write32(GPIO_PFR0, 0)
    c.write32(GPIO_PCR0, 0)
    gpio_in_p00_p1f = c.read32(GPIO_PDIR0)
    print('gpio_in_p00_p1f %08x' % (gpio_in_p00_p1f))
    # ugh...still 0x821f

    code.InteractiveConsole(locals=locals()).interact('Entering shell...')
