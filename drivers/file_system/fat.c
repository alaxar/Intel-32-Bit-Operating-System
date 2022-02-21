#include "fat.h"

struct bootRecord *boot_record_offset;
struct DirectoryEntry *root_directory_offset;
uint8_t *fat_table_offset;

void InitFAT() {
    boot_record_offset = (struct bootRecord*)0x7c00;
    fat_table_offset = (unsigned char *)0x7e00;
    root_directory_offset = (struct DirectoryEntry*)0x9000;
}

void SearchForFile(unsigned char *filename) {
    if(string_compare("test", "test") > 0) {
        __asm__("hlt");
    }
}