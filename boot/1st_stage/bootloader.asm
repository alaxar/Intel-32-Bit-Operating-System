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
	
	call fat12
	jmp $			; Jump to current address

; DATA INCLUSION
%include "boot/disk/disk.asm"
%include "boot/print.asm"
%include "boot/disk/fat12.asm"

; ===== [DATA Variables] =====
msgLoading	db	"Loading...", ENDL
DISK_ERROR	db "Read disk failed", ENDL
not_found_boot2 db "BOOT2.BIN not found, press any key to restart...", ENDL
boot2_cluster db 0

BOOT_SEGMENT equ 0x2000
BOOT_OFFSET equ 0x0
BOOT2_IMAGE db "ETHLDR  BIN"
KERNEL_IMAGE db "ETHKRNL BIN"

times 510-($-$$) db 0		; fill the rest with zeros.
db 0xAA55			; boot signature.