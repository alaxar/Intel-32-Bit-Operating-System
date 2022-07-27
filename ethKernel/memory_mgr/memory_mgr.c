#include "memory_mgr.h"

// very very simple memory allocator
void *free_base_addr = (void *)0x500000;
void *free_top_addr = (void *)0x7fef0000;

void memory_copy(char *source, char *dest, int no_bytes) {
    int i;
    for(i = 0; i < no_bytes; i++) {
        *(dest+i) = *(source+i);
    }
}

void memory_fill(char *address, int value, int size) {
    for(int i = 0; i < size; i++) {
        address[i] = value;
    }
}

void *page_allocator(int size) {
    void *allocated_address = free_base_addr;
    int freespace = (int)free_top_addr - (int)free_base_addr;
    if(freespace > size) {
        free_base_addr = free_base_addr + size;
        allocated_address = free_base_addr;
    } else
        return 0;

    return allocated_address;
}