

; GET VESA BIOS INFORMATION

get_vesa_bios_info:
    push es
    mov eax, dword 0x4F00
    mov edi, dword 0x2000
    int 0x10
    pop es

    ; check if the function succeeded or not.
    cmp al, 0x4f
    jne vesa_error

    jmp search_for_mode
    ret

search_for_mode:
    xor cx, cx
    mov si, 0x2022
    mov bx, word[si]
    call select_mode

select_mode:
    mov cx, word[si]

    cmp cx, 0xFFFF              ; cx is used to set mode number
    je vesa_error

    ; Get vesa mode info
    push es
    mov eax, 0x4f01
    mov edi, dword 0x2100
    int 0x10
    pop es

    cmp al, 0x4f
    jne next_mode

    ; check if the mode supports framebuffer
    mov ax, word [di]
    and ax, 0x80
    cmp ax, 0x80
    jne next_mode

    ; check resolution 
    ; width
    mov ax, word [di+18]
    cmp ax, 800
    jne next_mode

    ; height
    mov ax, word[di+20]
    cmp ax, 600
    jne next_mode

    ; bpp
    cmp byte[di+25], 24     ; if the bpp is less than 24 then don't use the mode.
    jb next_mode

    ; get frame buffer
    mov eax, [di+40]
    mov dword[VRAM], eax

    ; set chosen mode
    mov eax, 0x4f02
    mov bx, cx
    or bx, 0x4000
    int 0x10

    ret

next_mode:
    add si, 2
    jmp select_mode
    jmp $

vesa_error:
    mov esi, vesa_error_msg
    call print_string
    hlt

; For VESA BIOS
width dw 0
height dw 0
bpp db 0
segm dw 0
off dw 0
mode dw 0
VRAM dd 0