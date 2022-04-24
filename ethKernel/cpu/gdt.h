#pragma once

typedef struct gdt_entry {
    unsigned short limit_low;
    unsigned short base_low;
    unsigned char base_middle;
    unsigned char access_byte;
    unsigned char granularity;
    unsigned char base_high;
} __attribute__((packed)) gdt_entry;


typedef struct gdt_ptr {
    unsigned short limit;   /// limit or size of the gdt entry
    unsigned int base;      // base address of the gdt entry
} __attribute((packed)) gdt_ptr;

void set_gdt_gate(int num, unsigned long base, unsigned long limit, unsigned char access_byte, unsigned char granularity);
void gdt_install();