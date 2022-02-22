#include "fat.h"

struct bootRecord *boot_record_offset;
struct DirectoryEntry *root_directory_offset;
uint8_t *fat_table_offset;
uint32_t DirectoryEntryEnd;
void InitFAT() {
    boot_record_offset = (struct bootRecord*)0x7c00;
    fat_table_offset = (uint8_t *)0x7e00;
    root_directory_offset = (struct DirectoryEntry*)0x9000;
    DirectoryEntryEnd =  1 + (9*2) + 14;
}

void SearchForFile(unsigned char *filename) {
    int FileNotFound = 0, Entries = 0;
    while(FileNotFound == 0 && Entries < 224) {
        if(string_compare(filename, root_directory_offset->filename, string_length(filename)) > 0) {
            FileNotFound = 1;
            break;
        }

        // See the next entry in the root directory if not found.
        Entries++;
        root_directory_offset++;
    }
    if(FileNotFound == 0)
       printf("\nFile Not Found\n", -1, -1, 0);

    printf("FileSize: ", -1, -1, 0);
    printf(itoa(root_directory_offset->FileSize), -1, -1, 0);

    // ReadFileIntoMemory(root_directory_offset->LowFirstCluster, 0x909090);

}

void ReadFileIntoMemory(int FirstCluster, void* readBuffer) {
    uint32_t fat_offset;
    uint32_t lba;
    uint16_t currentCluster = FirstCluster;

    do {
        lba = DirectoryEntryEnd + (currentCluster - 2) * boot_record_offset->NoSecPerCluster;
        ReadingContents(lba, readBuffer);
        readBuffer += 512;

        // get the next cluster
        fat_offset = (currentCluster / 2) + currentCluster;

        if(currentCluster % 2 == 0) {
            currentCluster = (*(uint16_t*)(fat_table_offset + fat_offset)) & 0x0FFF;  // and with fff to get the lowest 12 bits.
        } else {
            currentCluster = (*(uint16_t*)(fat_table_offset + fat_offset)) >> 4;      // shift by 4 bits to get the highest 12 bits
        }

        printf((itoa(currentCluster)), -1, -1, 0);
        printf("\n", -1, -1, 0);

    } while(currentCluster < 0x0FF8);       // while end of file.
}

void ReadingContents(uint32_t lba, void *readBuffer) {
    uint8_t *buffer = (uint8_t*)0x100000;
    // 1 + 18 + 14
}
void ListFiles() {

}