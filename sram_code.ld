MEMORY {
    /* Actual flash/sram sizes depend on exact model */
    flash : ORIGIN = 0, LENGTH = 0x40000
    sram0 : ORIGIN = 0x1ff80000, LENGTH = 0x80000
    sram1 (rwx): ORIGIN = 0x20000000, LENGTH = 0x80000
    /* mirrored */
    rom : ORIGIN = 0x20080000, LENGTH = 0x2000
}

ENTRY(sram_entry)

/* This address/struct layout is hardcoded in ROM */
usb0_ep_states = ORIGIN(sram1) + 0x2E6C;

SECTIONS {
    /DISCARD/ : { *(.comment) *(.got) }
    .init : { *(.init) *(.init.*) }
    .text : { *(.text) *(.text.*) }
    .data : { *(.data) *(.data.*) }
    .rodata : { *(.rodata) *(.rodata.*) }
    .bss : { *(.bss) *(.bss.*) *(COMMON) }
}
