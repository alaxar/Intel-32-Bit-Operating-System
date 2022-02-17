;
;   ETHIOPIC OPERATING SYSTEM Copyright 2014
;   This bootloader file is to provide the neccessary information about the hardware to the kernel
;   This program is responsible for loading the VBE, Detect Memory, enable a20 and GDT

%define ENDL 0xD, 0xA, 0x0


[org 0x1000]
[bits 16]
start:
    ; Enabling A20 Line
    call enableA20

    ; loading the kernel
    mov si, loadingKernel
    call print_string
    ; call load_kernel

    mov si, switch
    call print_string

    ; Switching to Protected Mode
    call switch_to_pm
    
    jmp $

%include "boot/gdt.asm"
%include "boot/switch_to_pm.asm"
%include "boot/a20.asm"
%include "boot/print.asm"
%include "boot/2nd_stage/disk.asm"
%include "boot/print_string.asm"            ; to print on 32 protected mode

; Protected Mode
[bits 32]
BEGIN_PM:
    mov esi, msg_protected_mode
    call print_string_pm
    jmp dword 0x3000
    jmp $

switch db "Switching into Protected Mode.", ENDL
loadingKernel db "Loading the ethKernel...", ENDL
KERNEL_IMAGE db "ETHKRNL BIN"
BOOT2_IMAGE db "ETHLDR  BIN"
not_found_kernel db "ETHKERNEL.BIN is not found. press any key to restart...", ENDL
KERNEL_DRIVE db 0
BOOT_OFFSET db 0
kernel_cluster db 0
KERNEL_OFFSET equ 0x10000
msg_protected_mode db "Protected Mode Entered!", 0