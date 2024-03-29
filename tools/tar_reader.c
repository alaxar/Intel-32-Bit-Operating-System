#include "tar_reader.h"

struct tar_header *tar_hdr;
unsigned int getsize(const char *in)
{
 
    unsigned int size = 0;
    unsigned int j;
    unsigned int count = 1;
 
    for (j = 11; j > 0; j--, count *= 8)
        size += ((in[j - 1] - '0') * count);
 
    return size;
}


unsigned char *FindFileTAR(char *filename) {

    // get the memory address of initram from grub multiboot header
    multiboot_module_t *mod = (multiboot_module_t*)mbi->mods_addr;

    int i = 0, isFound = 0, FileSize;
    unsigned char *initram_addr = (unsigned char *)mod->mod_start;          // starting address of initram
    do {
        tar_hdr = (struct tar_header*)initram_addr;
        FileSize = getsize(tar_hdr->size);
        if(string_compare(filename, tar_hdr->filename, string_length(filename)) == 0) {
            initram_addr = initram_addr + sizeof(struct tar_header) + ((FileSize / 512) + 1) * 512;
            printf(tar_hdr->filename, -1, -1, 0);  //+ 0x200 + 0x2d8a + 0x76
        } else {
            isFound = 1;
        }

    if(isFound == 1)
        break;

    } while(tar_hdr->filename[0] != 0);

    // get to the data region
    initram_addr = initram_addr + 512;

    if(isFound == 0)
        printf("File not found\n", -1, -1, 0);
    else
        return initram_addr;
}

unsigned char *ReadTarFile(struct tar_header *found_header, unsigned char *address) {
    unsigned char *buffer;
    int FileSize = getsize(found_header->size);
    for(int i = 0; i < FileSize; i++) {
        *(buffer+i) = *(address+i);
    }
    // buffer[FileSize] = 0;
    return address;          // return the address of the found file.
}