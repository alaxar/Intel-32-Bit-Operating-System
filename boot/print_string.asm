[bits 32]

VIDEO_MEMORY equ 0xb8000
WHITE_ON_BLACK  equ 0x0f

; prints a null-terminated string pointed to by EDX
print_string_pm:
    pusha
    mov edx, VIDEO_MEMORY

print_string_pm_loop:
    lodsb
    mov ah, WHITE_ON_BLACK

    cmp al, 0
    je done_pm

    mov [edx], ax
    add edx, 2

    jmp print_string_pm_loop

done_pm:
    popa
    ret    