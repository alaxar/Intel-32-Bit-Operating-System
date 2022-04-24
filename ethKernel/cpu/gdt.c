#include "gdt.h"

gdt_entry gdt[3];               //  null, code, data
gdt_ptr gdt_pointer;            // pointer to gdt entry

void set_gdt_gate(int num, unsigned long base, unsigned long limit, unsigned char access_byte, unsigned char granularity) {
    // base address
    gdt[num].base_low = (base & 0xFFFF);
    gdt[num].base_middle = (base >> 16) & 0xFF;
    gdt[num].base_high = (base >> 24) & 0xFF;

    // limit address
    gdt[num].limit_low = (limit & 0xFFFF);
    gdt[num].granularity = (limit >> 16) & 0x0F;

    // granularity
    gdt[num].granularity |= (granularity & 0xF0);
    gdt[num].access_byte = access_byte;
}

void gdt_install() {
    // set lgdt pointer

    gdt_pointer.limit = (sizeof(gdt_entry) * 3) - 1;
    gdt_pointer.base = (unsigned int)&gdt;


    set_gdt_gate(0, 0, 0, 0, 0);                        // NULL desc
    set_gdt_gate(1, 0x0, 0xffffffff, 0x9A, 0xCF);       // code segment
    set_gdt_gate(2, 0x0, 0xffffffff, 0x92, 0xCF);       // data segment

    _gdt_flush();
}