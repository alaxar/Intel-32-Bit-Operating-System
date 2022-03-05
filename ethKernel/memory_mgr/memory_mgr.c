#include "memory_mgr.h"

char *heap = 0x4C4B40;
void *memory_allocate(int size) {
    char *starting_address;
    starting_address = heap = mem_check();
    for(int i = 0; i < size; i++) {
        *heap = *(heap+i) | 0x01;
        heap++;
    }

    return starting_address;
}

char* mem_check() {
    while(*heap & 0x1) {
        heap++;
    }
    return heap;
}