OUTPUT_FORMAT("binary)
ENTRY (start)
SECTIONS 
{
    .text 0x4000 : {
        *(.text)
    }

    .data : {
        *(.data)
    }

    .bss : {
        *(.bss)
    }
}