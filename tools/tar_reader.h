#ifndef TAR_READER_HEADER
#define TAR_READER_HEADER

struct tar_header
{
    char filename[100];
    char mode[8];
    char uid[8];
    char gid[8];
    char size[12];
    char mtime[12];
    char chksum[8];
    char typeflag[1];
    char padding[355];
} __attribute__((packed));

extern struct tar_header *tar_hdr;

unsigned int getsize(const char *in);
int ReadTarFile(char *filename);
#endif