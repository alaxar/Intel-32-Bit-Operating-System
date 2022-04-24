; Multiboot header definition

MAGIC_NUMBER    equ     0x1BADB002
ALIGN_MEM       equ     1<<0
MEM_INFO        equ     1<<1
VBE_INFO        equ     1<<2
FLAGS           equ     ALIGN_MEM | MEM_INFO | VBE_INFO
CHECKSUM        equ     -(MAGIC_NUMBER + FLAGS)

section .text
global _start

align 4
    dd MAGIC_NUMBER
    dd FLAGS
    dd CHECKSUM
    dd 0, 0, 0, 0, 0
    dd 0                ; Set graphics mode
    dd 800, 600, 32     ; set the resolution the default


_start:

    ; setup the stack
    mov esp, 0x7e00
    mov ebp, esp


    push eax
    push ebx

    extern main
    call main

    %include "boot/interrups.asm"

    jmp $

global _gdt_flush
extern gdt_pointer

_gdt_flush:

    lgdt[gdt_pointer]           ; load the gdt

    ; flushing cpu pipeline

    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax

    jmp 0x08:flush

flush:
    ret