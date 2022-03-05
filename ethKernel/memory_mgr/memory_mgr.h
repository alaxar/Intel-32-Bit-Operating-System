#ifndef _MEMORY_H_
#define _MEMORY_H_

extern char *end_of_kernel;

void *memory_allocate(int size);
char* mem_check();
void page_allocator();

#endif