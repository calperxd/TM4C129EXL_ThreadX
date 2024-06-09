MEMORY
{
    FLASH (rx) : ORIGIN = 0x00000000, LENGTH = 1024K
    SRAM (rwx) : ORIGIN = 0x20000000, LENGTH = 256K
}

SECTIONS
{
    .text :
    {
        _text = .;
        KEEP(*(.isr_vector))     /* Interrupt vectors */
        *(.text*)                /* Code */
        *(.rodata*)              /* Read-only data */
        _etext = .;
    } > FLASH

    .ARM.exidx : AT(ADDR(.text) + SIZEOF(.text) + 4096)
    {
        . = ALIGN(4);
        *(.ARM.exidx*)
        . = ALIGN(4);
    } > FLASH

    .eh_frame : AT(ADDR(.ARM.exidx) + SIZEOF(.ARM.exidx) + 4096)
    {
        . = ALIGN(4);
        *(.eh_frame*)
        . = ALIGN(4);
    } > FLASH

    .data : AT(ADDR(.eh_frame) + SIZEOF(.eh_frame) + 4096)
    {
        . = ALIGN(4);
        _data = .;
        _ldata = LOADADDR(.data);
        *(vtable)
        *(.data*)
        . = ALIGN(4);
        _edata = .;
    } > SRAM
    _end = _edata;
    PROVIDE(end = _edata);
    PROVIDE(__RAM_segment_used_end__ = _edata);

    .bss :
    {
        . = ALIGN(4);
        _bss = .;
        *(.bss*)
        *(COMMON)
        . = ALIGN(4);
        _ebss = .;
    } > SRAM

    /* Heap and stack section definitions */
    .heap (COPY):
    {
        . = ALIGN(8);
        __end__ = .;
    } > SRAM

    _heap = ORIGIN(SRAM) + LENGTH(SRAM) - 0x10000;
    __HeapBase = _heap;
    __HeapLimit = ORIGIN(SRAM) + LENGTH(SRAM);
    _stack = ORIGIN(SRAM);
    __StackTop = ORIGIN(SRAM) + LENGTH(SRAM);
}
