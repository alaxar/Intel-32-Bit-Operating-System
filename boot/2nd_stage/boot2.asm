;
;   ETHIOPIC OPERATING SYSTEM Copyright 2014
;   This bootloader file is to provide the neccessary information about the hardware to the kernel
;   This program is responsible for loading the VBE, Detect Memory and GDT

start:
    mov si, testing
    call print_string

    jmp $

%include "boot/print.asm"

testing db "It worked", 13, 10, 0