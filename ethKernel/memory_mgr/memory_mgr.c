#include "memory_mgr.h"

// very very simple memory allocator
void *free_base_addr = (void *)0x4C4B40;
void *free_top_addr = (void *)0x17D7840;

void *page_allocator(int size) {
    void *allocated_address = free_base_addr;
    int freespace = (int)free_top_addr - (int)free_base_addr;
    if(freespace > size)
        free_base_addr = free_base_addr + size;
    else
        return 0;

    return allocated_address;
}