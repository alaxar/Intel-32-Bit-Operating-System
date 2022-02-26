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

    ; setting up vesa video mode
    call get_vesa_bios_info

    ; Setting up the Opeating system 32 bit environment.
    mov si, switch
    call print_string

    ; Switching to Protected Mode
    call switch_to_pm
    
    jmp $

%include "boot/vesa_vbe/vbe.asm"
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
    jmp dword 0x4000
    jmp $

switch db "Setting up the operating system 32 bit environment....", ENDL
loadingKernel db "Loading the ethKernel...", ENDL
KERNEL_IMAGE db "ETHKRNL BIN"
BOOT2_IMAGE db "ETHLDR  BIN"
not_found_kernel db "ETHKERNEL.BIN is not found. press any key to restart...", ENDL
vesa_error_msg db "Error while setting up Video Mode.", ENDL
KERNEL_DRIVE db 0
BOOT_OFFSET db 0
kernel_cluster db 0
KERNEL_OFFSET equ 0x10000
VESA_OFFSET equ 0x2000

msg_protected_mode db "Protected Mode Entered!", 0