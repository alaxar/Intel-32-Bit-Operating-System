;
;   ETHIOPIC OPERATING SYSTEM Copyright 2014
;   This bootloader file is to provide the neccessary information about the hardware to the kernel
;   This program is responsible for loading the VBE, Detect Memory, enable a20 and GDT



[org 0]

times 2048 db 'A'
start:
    mov si, testing
    call print_string

    jmp $

%include "boot/print.asm"
testing db "Hello, this is the kernel", 13, 10, 0