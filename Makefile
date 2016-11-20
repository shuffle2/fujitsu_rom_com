ARM := arm-linux-gnueabi-
CFLAGS := -nostdlib -Os -mthumb -mcpu=cortex-m3 \
    -Wall -Wl,--build-id=none,-T,sram_code.ld

SOURCES := sp_xfer.c sp_serv.c
INCLUDES := common.h platform.h sp_xfer.h

OBJS := $(patsubst %.S,%.o,$(patsubst %.c,%.o,$(SOURCES)))
DEPS := $(OBJS) $(SOURCES) $(INCLUDES) Makefile sram_code.ld

all: sram_code.elf sram_code.bin

%.o: %.c *.h
	$(ARM)gcc -c $(CFLAGS) -o $@ $<

sram_code.elf: $(DEPS)
	$(ARM)gcc $(CFLAGS) $(OBJS) -o $@

%.bin: %.elf
	$(ARM)objcopy -O binary $< $@

clean:
	rm -f sram_code.elf sram_code.bin $(OBJS)
