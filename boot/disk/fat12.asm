fat12:

load_fat_table:
    mov ax, 1               ; lba value (sector 2) where fat table located.
    mov cx, 9              ; how many sectors you want to read
    mov dl, 0               ; drive number
    mov bx, 0x7e00          ; where fat table data will be loaded
    call disk_read

load_root_directory:
    mov ax, 19
    mov cx, 14
    mov dl, 0
    mov bx, 0x9000          ; where root directory loaded
    call disk_read

find_boot2_image:
    mov di, 0x9000
    mov bx, 0
    
search:
    ; search for file
    mov si, BOOT2_IMAGE
    mov cx, 11              ; File name count
    push di
    repe cmpsb
    pop di
    je .found_boot2

    add di, 32
    inc bx
    cmp bx, 224
    jl search

    jmp boot2_image_not_found

.found_boot2
    ; mov si, di
    ; call print_string
    mov ax, [di + 26]
    mov [boot2_cluster], ax

    ; setting up the second boot load area
    mov bx, BOOT_SEGMENT                        ; this must be an input
    mov es, bx
    mov bx, BOOT_OFFSET                         

    ; Saving drive number
    mov dl, [drive_number]

load_boot2:
    ; calculate lba (1 + 18 + 14 + (clusterNumber - 2) * SectorsPerCluster
    ; mov ax, 3
    ; mov [boot2_cluster], ax
    mov ax, [boot2_cluster]     ; moving boot2 cluster value to ax
    mov dx, 33                  ; the end of root directory (right after the root_dir is the data region)
    sub ax, 2                   ; cluster subtractor
    mov cl, [NoSecPerCluster]   ; this is the last multiplier (SectorsPerCluster)
    mul word cl
    add ax, dx

    ; loading the kernel into memory pointed by bx
    ; parameters
    ; lba = ax
    ; driverNumber = dl
    ; number of sectors to read = cl
    ;
    mov dl, [drive_number]
    mov cl, 1
    ; now read
    call disk_read

    ; increment bx by 512 to reserve a space for the next cluster
    add bx, [BytesPerSector]
    mov [BOOT_OFFSET], bx               ; save the bx pointer into boot_offset to prevent it from change.
    ; calculate the fat table offset 
    ; formula
    ; fat_offset = (currentCluster / 2) + currentCluster
    mov ax, [boot2_cluster]         ; copy the currentCluster to ax (currentCluster)
    push ax                         ; save ax into stack for later use
    mov cl, 2                       ; cl will be used to divide the currentCluster (currentCluster / 2)
    div word cl                     ; now divide ax by cl which is (currentCluster / 2)
    pop cx                          ; restore the value of ax from stack into bx (currentCluster)
    add ax, cx                      ; add values (currentCluster / 2 ) + currentCluster
                                    ; ax contains the division part bx contains the currentCluster popped from the stack.
    xor ah, ah                      ; clearing the upper bits
    ; now the value of fat_offset is stored in ax
    ; now check if the currentCluster is whether an even or odd number
    ; if even keep the lowest 12 bits, else keep the highest 12 bits

    push ax                          ; save ax into stack(fat_Offset)
    mov ax, cx                       ; cx currentCluster get the currentCluster for division
    mov dl, 2                        ; used to divide the currentCluster to check for even or odd
    div byte dl

    ; when dividing if the operand is a byte the the cooffcient is stored in al and remainder in ah.

    cmp ah, 0                           ; if ah is 0 its even else its odd.

    je even                             ; if true then jump to even.

    jmp odd                             ; else jump to odd.

even:
    xor cx, cx
    pop cx                              ; bx contains fat_offset

    push bx
    xor bx, bx

    mov bx, cx
    xor dx, dx                          ; clearing dx
    mov dx, word [0x7e00+bx]            ; where fat is loaded (fat_entry+fat_offset)

    and dx, 0x0FFF
    mov [boot2_cluster], dx
    call is_end_of_file

odd:
    xor cx, cx
    pop cx                              ; bx contains fat_offset

    push bx
    xor bx, bx

    mov bx, cx
    xor dx, dx                          ; clearing dx
    mov dx, word [0x7e00+bx]            ; where fat is loaded (fat_entry+fat_offset)

    shr dx, 4
    mov [boot2_cluster], dx
    call is_end_of_file
    jmp $


is_end_of_file:
    mov bx, [BOOT_OFFSET]
    cmp dx, 0x0FF8
    jl load_boot2

    ; jump to the second boot loader
    mov ax, BOOT_SEGMENT
    mov ds, ax
    mov es, ax


    jmp BOOT_SEGMENT:BOOT_OFFSET

    jmp $

boot2_image_not_found:
    mov si, not_found_boot2
    call print_string
    call wait_key_press