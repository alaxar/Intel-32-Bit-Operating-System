OUTPUT_FORMAT("binary)
ENTRY (main)
SECTIONS 
{
    .text 0x3000 : {
        *(.text)
    }

    .data : {
        *(.data)
    }

    .bss : {
        *(.bss)
    }
}