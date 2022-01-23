;
;	ETHIOPIC 32 Bit Operating System
;	

[org 0x7c00]
[bits 16]

; DATA DECLARATION
%define ENDL 0xD, 0xA


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
	
	mov si, settingUpStack
	call print_string

	; setup the stack
	mov bp, 0x7e00
	mov sp, bp
	
	
	
	jmp $			; Jump to current address



; DATA INCLUSION
%include "boot/print.asm"

; ===== [DATA Variables] =====
msgLoading	db	"Loading...", ENDL, 0
settingUpStack db "Setting up stack...", ENDL, 0

times 510-($-$$) db 0		; fill the rest with zeros.
db 0xAA55			; boot signature.