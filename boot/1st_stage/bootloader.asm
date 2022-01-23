;
;	ETHIOPIC 32 Bit Operating System
;	

[org 7c00]

jmp short bootload_entry
nop

; ===== [FAT Header] =====


%include "FAT_BPB.inc"


; ===== [DATA Variables] =====
msgLoading	db	"Loading...", 0, 13


bootload_entry:

	;setup data segment since code segment is already setted up by the bios.
	mov ax, 0			; use used ax since we can't directly assign a value to segment registers
	mov ds, ax
	mov es, ax
	
	; setup the stack
	mov bp, 0x7e00
	mov sp, bp
	
	
	
	jmp $			; Jump to current address


; DATA DECLARATION
%define ENDL	0xD0, 0x0A

; DATA INCLUSION
%include "../print.asm"

times 510-($-$$) db 0		; fill the rest with zeros.
db 0xaa55			; boot signature.
