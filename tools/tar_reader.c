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


int ReadTarFile(char *filename) {
    int i = 0;
    unsigned char *initram_addr = (unsigned char *)0x10000;
    tar_hdr = (struct tar_header*)initram_addr;

    do {
        if(string_compare(filename, tar_hdr->filename, string_length(filename)) == 0)
            tar_hdr = (struct tar_header*)initram_addr;//+getsize(tar_hdr->size);
             
    
        
        printf(sizeof(struct tar_header) + 11111, -1, -1, 0);
    } while(tar_hdr->filename[0] != '\0');
}