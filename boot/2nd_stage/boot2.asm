;
;   ETHIOPIC OPERATING SYSTEM Copyright 2014
;   This bootloader file is to provide the neccessary information about the hardware to the kernel
;   This program is responsible for loading the VBE, Detect Memory, enable a20 and GDT

%define ENDL 0xD, 0xA, 0x0


[org 0]
[bits 16]
start:
    ; enable A20
    ; call enableA20
    call load_kernel
    call switch_to_pm
    
    jmp $

%include "boot/print.asm"
%include "boot/gdt.asm"
%include "boot/switch_to_pm.asm"
%include "boot/a20.asm"
%include "boot/2nd_stage/disk_driver.asm"

[bits 16]
load_kernel:
	mov [KERNEL_DRIVE], dl
	mov bx, KERNEL_OFFSET
	mov dl, [KERNEL_DRIVE]
    call disk_load
	ret

[bits 32]
BEGIN_PM:
;    mov [0xb8000], 'A'
   jmp $


testing db "Hello, this is the second bootloader", ENDL
WELCOME db "Kernel is "
KERNEL_DRIVE db 0
KERNEL_OFFSET equ 0x1000

msg_protected_mode db "Protected Mode Entered!", ENDL