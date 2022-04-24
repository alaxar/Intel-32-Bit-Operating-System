#include "bmp.h"

unsigned char *bmp_header_offset;       // used for storing address of bmp header file into char pointer
BMPHeader *bmp_header;
int isflipped = 0;

DIB *ReadBMP(char *filename) {

    bmp_header_offset = FindFileTAR(filename);        // returning address of the file from the tar file

    bmp_header = (BMPHeader*)bmp_header_offset;  // bmp header

    if(bmp_header->type != 0x4D42) {
        printf("The file is not BMP or corrupted\n", -1, -1, 0);
        return -1;
    }

    // reading the dib header
    DIB *dib_header = (DIB*)(bmp_header_offset + 14);

    if(dib_header == 0x0)
        return 0x0;

    return dib_header;
}

unsigned char GrayScale(unsigned char B, unsigned char G, unsigned char R) {
    return ((R + G + B) / 3);
}


void DrawImage(int x, int y, DIB *dib_header) {
    // calculating how many bytes are needed to fill one row
    int RowSize = ((dib_header->bpp * dib_header->width + 31) / 32) * 4;
    int PixelArraySize = RowSize * absolute(dib_header->height);

    unsigned char *PixelData = bmp_header_offset + bmp_header->offset;

    unsigned char temp;
    int red, green, blue, alpha = 0;
    int colorBMP;

    // collecting pixels in to and array
    if(isflipped == 0) {
        for(int i = 0; i < dib_header->height; i++) {
            for(int j = 0; j < RowSize; j += 3) {
                temp = PixelData[(i*RowSize+j)];
                PixelData[(i*RowSize+j)] = PixelData[(i*RowSize+j) + 2];
                PixelData[(i*RowSize+j) + 2] = temp;
            }
        }
        isflipped = 1;
    }
    
    // drawing image to screen
    for(int i = dib_header->height; i > 0; i--) {
        for(int j = dib_header->width; j > 0; j--) {
            int kk = 3 * j;

            red = PixelData[i*RowSize+kk];
            green = PixelData[(i*RowSize+kk) + 1];
            blue = PixelData[(i*RowSize+kk) + 2];


            // forming one color from three distnic colors
            colorBMP = (int)(colorBMP << 8) | red;
            colorBMP = (int)(colorBMP << 8) | green;
            colorBMP = (int)(colorBMP << 8) | blue;
            PutPixel(j + x, i + y, colorBMP);
        }
    }
}

void RotateImage() {}