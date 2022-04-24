#pragma once

typedef struct bmp_struct {
    unsigned short type;
    unsigned int size;
    unsigned int reserved;
    unsigned int offset;
} __attribute__((packed)) BMPHeader;

typedef struct dib_struct {
    unsigned int HeaderSize;
    int width;
    int height;
    unsigned short colorplanes;
    unsigned short bpp;
    unsigned int compression;
    unsigned int imageSize;
    int horizontalRes;
    int verticalRes;
    unsigned int colorPalette;
    unsigned int ImportantColors;
} DIB;

DIB *ReadBMP(char *filename);
void DrawImage(int x, int y, DIB *dib_header);