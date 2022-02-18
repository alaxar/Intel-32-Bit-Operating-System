;
;	ETHIOPIC 32 Bit Operating System
;	

[org 0x7c00]
[bits 16]

; DATA DECLARATION
%define ENDL 0xD, 0xA, 0x0


jmp short bootload_entry
nop

;
; ===== [FAT Header] =====
;	BPB

%include "boot/1st_stage/FAT_BPB.inc"


bootload_entry:
	; Loading message
	mov si, msgLoading
	call print_string

	;setup data segment since code segment is already setted up by the bios.
	mov ax, 0			; use used ax since we can't directly assign a value to segment registers
	mov ds, ax
	mov es, ax
	
	; setup the stack
	mov bp, 0x7c00
	mov sp, bp

	; clearing registers
	xor ax, ax
	
	; 	KERNEL LOADIN AT 0x5000:0x0
	; 	loading the ethKernel into memory
	;
	
	mov si, KERNEL_IMAGE			; Input name of the Image 
	mov ax, word 0x0
	mov [BOOT_SEGMENT], ax
	mov ax, word 0x4000
	mov [BOOT_OFFSET], ax
	call fat12					; calling the file system.

	; clearing vars and mems
	xor ax, ax
	mov [BOOT_SEGMENT], ax
	mov [BOOT_OFFSET], ax

	;	2ND STAGE BOOTLOADER
	; 	loading the second bootloader into memory
	;

	mov si, BOOT2_IMAGE			; Input name of the Image 
	mov ax, word 0x0
	mov [BOOT_SEGMENT], ax
	mov ax, word 0x1000
	mov [BOOT_OFFSET], ax
	call fat12					; calling the file system.

	; ; set segment registers accordingly for the second stage bootloader.
    ; mov ax, [BOOT_SEGMENT]
    ; and al, 0x0                         ; removing the last byte added by the cpu
    ; mov ds, ax
    ; mov es, ax
    ; mov fs, ax
    ; mov gs, ax
	; mov ss, ax

	jmp 0x1000				; far jump to the second bootloader.
	
	jmp $			; Jump to current address

; DATA INCLUSION
%include "boot/disk/disk.asm"
%include "boot/print.asm"
%include "boot/disk/fat12.asm"

; ===== [DATA Variables] =====
msgLoading	db	"", ENDL
DISK_ERROR	db "Read disk failed", ENDL
not_found_boot2 db "BOOT2.BIN not found", ENDL
boot2_cluster db 0

BOOT_SEGMENT dw 0x0000
BOOT_OFFSET dw 0x0000
BOOT2_IMAGE db "ETHLDR  BIN"
KERNEL_IMAGE db "ETHKRNL BIN"

times 510-($-$$) db 0		; fill the rest with zeros.
db 0xAA55			; boot signature.