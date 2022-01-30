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
	mov bp, 0x9000
	mov sp, bp
	
	; disk read
	mov si, kernel_loading
	call print_string

	mov [drive_number], dl
	mov ax, 1
	mov cl, 50
	mov bx, 0x1000

	call disk_read

	jmp 0x1000

	jmp $			; Jump to current address



; DATA INCLUSION
%include "boot/disk/disk.asm"
%include "boot/print.asm"

; ===== [DATA Variables] =====
msgLoading	db	"Loading...", ENDL, 0
kernel_loading db "Loading the Kernel to memory...", ENDL, 0
settingUpStack db "Setting up stack...", ENDL, 0
DISK_ERROR	db "Read disk failed", ENDL, 0
DISK_SUCCESS db "Read disk Success", ENDL, 0

times 510-($-$$) db 0		; fill the rest with zeros.
db 0xAA55			; boot signature.