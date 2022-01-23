print_string:
	lodsb			; mov al, si
	mov ah, 0x0e
	or al, al
	jz .done
	int 0x10
	jmp print_string

.done:
	ret
