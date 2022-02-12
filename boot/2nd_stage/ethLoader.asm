;
;   ETHIOPIC OPERATING SYSTEM Copyright 2014
;   This bootloader file is to provide the neccessary information about the hardware to the kernel
;   This program is responsible for loading the VBE, Detect Memory, enable a20 and GDT

%define ENDL 0xD, 0xA, 0x0


[org 0x20000]
[bits 16]
start:
    ; enable A20
    call enableA20
    ; call load_kernel
    mov si, testing
    call print_string
    call switch_to_pm
    
    jmp $

%include "boot/gdt.asm"
%include "boot/print.asm"
%include "boot/switch_to_pm.asm"
%include "boot/a20.asm"
%include "boot/2nd_stage/disk_driver.asm"
%include "boot/print_string.asm"
[bits 32]
BEGIN_PM:
    mov esi, msg_protected_mode
    call print_string_pm
    jmp $

testing db "Hello, this is the second bootloader", ENDL
KERNEL_DRIVE db 0
KERNEL_OFFSET equ 0x10000

msg_protected_mode db "Protected Mode Entered!", 0