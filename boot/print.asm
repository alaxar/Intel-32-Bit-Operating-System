print_string:
	lodsb			; mov al, si
	or al, al
	mov ah, 0x0e
	int 0x10
	jz .done
	jmp print_char

.done:
	ret
