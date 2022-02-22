#ifndef _FAT_HEADER
#define _FAT_HEADER

#include "../../include/types.h"
#include "../../include/strings.h"

typedef struct bootRecord{
	uint8_t BootJumpInstrution[3];
	uint8_t OEM_Identifier[8];
	uint16_t BytesPerSector;
	uint8_t NoSecPerCluster;
	uint16_t NoReservedSec;
	uint8_t NoFATTables;
	uint16_t NoRootDirectories;
	uint16_t TotalNoSectors;
	uint8_t MediaTypeDesc;
	uint16_t NumberofSectorsPerFat;
	uint16_t NumberofSectorsPerTrack;
	uint16_t NumberOfHeader;
	uint32_t NumberOfHiddenSec;
	uint32_t LargeSectorCount;

	uint8_t drive_number;	
	uint8_t Reserved;
	uint8_t Signature;
	uint32_t Volumes_id;	
	uint8_t Volume_label[11];
	uint8_t System_identifier[8];
} __attribute__((packed)) bootRecord;

typedef struct DirectoryEntry {
	uint8_t filename[11];
	uint8_t attributes;
	uint8_t reserved;
	uint8_t CreationTime;
	uint16_t CreatedTime;
	uint16_t CreatedDate;
	uint16_t LastAccessed;
	uint16_t HighFirstCluster;		// this is always zero for fat12 and fat16
	uint16_t LastModifiedTime;
	uint16_t LastModifiedDate;
	uint16_t LowFirstCluster;		// use this number to find the first cluster of this entry(file)
	uint32_t FileSize;			// size of the file in bytes
} __attribute__((packed)) DirectoryEntry;



extern struct bootRecord *boot_record_offset;
extern struct DirectoryEntry *root_directory_offset;
extern uint8_t *fat_table_offset;

void SearchForFile(unsigned char *filename);
void ReadFileIntoMemory(int FirstCluster, void* readBuffer);
void ReadingContents(uint32_t lba, void* readBuffer);
#endif