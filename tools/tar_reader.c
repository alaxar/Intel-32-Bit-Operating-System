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


char* FindFileTAR(char *filename) {
    int i = 0, isFound = 0, FileSize;
    unsigned char *initram_addr = (unsigned char *)0x10000;
    // printf(tar_hdr->filename, -1, -1, 0);  + 0x200 + 0x2d8a + 0x76
    do {
        tar_hdr = (struct tar_header*)initram_addr;
        FileSize = getsize(tar_hdr->size);
        if(string_compare(filename, tar_hdr->filename, string_length(filename)) == 0) {
            initram_addr = initram_addr + sizeof(struct tar_header) + ((FileSize / 512) + 1) * 512;
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
        return ReadTarFile(tar_hdr, initram_addr);

}

char *ReadTarFile(struct tar_header *found_header, unsigned char *address) {
    unsigned char *buffer;
    int FileSize = getsize(found_header->size);
    for(int i = 0; i < FileSize; i++) {
        *(buffer+i) = *(address+i);
    }

    return buffer;          // return the address of the found file.
}