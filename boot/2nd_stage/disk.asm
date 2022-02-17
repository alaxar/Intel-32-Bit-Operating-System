;
; LBA Addressing Scheme Conversion to CHS
; ax = LBA
; CH - cylinder, CL - sector, DH - head 
wait_key_press:
    mov ah, 0x0
    int 0x16
    jmp 0xFFFF:0            ; bios beggining


lba_to_chs:

    push ax
    push dx

    xor dx, dx                          ; dx = 0
    div word [NumberofSectorsPerTrack]    ; ax = LBA / SectorsPerTrack
                                        ; dx = LBA % SectorsPerTrack

    inc dx                              ; dx = (LBA % SectorsPerTrack + 1) = sector
    mov cx, dx                          ; cx = sector

    xor dx, dx                          ; dx = 0
    div word [NumberOfHeader]                ; ax = (LBA / SectorsPerTrack) / Heads = cylinder
                                        ; dx = (LBA / SectorsPerTrack) % Heads = head
    mov dh, dl                          ; dh = head
    mov ch, al                          ; ch = cylinder (lower 8 bits)
    shl ah, 6
    or cl, ah                           ; put upper 2 bits of cylinder in CL

    pop ax
    mov dl, al                          ; restore DL
    pop ax
    ret
;
; CHS Addressing Scheme
;   ax - lba
;   cl - number of sectors to read
;   dl - drive number

disk_read
    push cx
    call lba_to_chs
    pop ax

    mov ah, 0x02
    int 0x13

    jc disk_error

    cmp al, al
    jne disk_error

    ret

disk_error:
    mov si, DISK_ERROR
    call print_string
    call wait_key_press

NumberofSectorsPerTrack db 18
NumberOfHeader db 2
DISK_ERROR DB "Error while reading disk...", ENDL