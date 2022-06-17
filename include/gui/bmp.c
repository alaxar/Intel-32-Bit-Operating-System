#include "bmp.h"

unsigned char *bmp_header_offset;       // used for storing address of bmp header file into char pointer
BMPHeader *bmp_header;
int isSwapped = 0;
unsigned char tempColor;
unsigned char *PixelData;
int PixelArraySize;
int Height;
int Width;
int bpp;
int RowSize;
int red, green, blue, colorBMP;

void flip_image_array(unsigned char **ImageData, int rows, int cols) {
    int i, j;
    long rd2;
    unsigned char **temp;

    temp = page_allocator(rows * cols);

    rd2 = rows / 2;

    for(i = 0; i < rd2; i++) {
        for(int j = 0; j < cols; j++) {
            temp[rows-1-i][j] = ImageData[i][j];
        }
    }

}

DIB *ReadBMP(char *filename) {

    bmp_header_offset = FindFileTAR(filename);        // returning address of the file from the tar file

    bmp_header = (BMPHeader*)bmp_header_offset;  // bmp header

    if(bmp_header->type != 0x4D42) {
        printf("The file is not BMP or corrupted\n", -1, -1, 0);
        return -1;
    }

    // reading the dib header
    DIB *dib_header = (DIB*)(bmp_header_offset + 14);

    // now we can allocate memory for our image 
    PixelData = bmp_header_offset + bmp_header->offset;

    if(dib_header == 0x0)
        return 0x0;

    return dib_header;
}

unsigned char GrayScale(unsigned char B, unsigned char G, unsigned char R) {
    return ((R + G + B) / 3);
}


void DrawImage(int x, int y, DIB *dib_header) {
    // check whether the image width in bytes are a multiple of 4 bytes or not
    Width = dib_header->width;
    Height = dib_header->height;
    bpp = dib_header->bpp;                            // expressed in bits
    RowSize = Width * (bpp / 8);                // multiplying the width by byte per pixel to get the actual size need to store the pixel data

    if(RowSize % 4 != 0 && bpp == 24) {                          // check if the rowsize is not a multiple of 4 bytes.
        // if the row is not a multiple of 4 bytes.
        // then calculate the rowsize and round it up to a multiple of 4 bytes.
        // to calculate RowSize to a multple of 4 bytes we use the below formula
        // RowSize = floor(bpp * ImageWidth + 31 / 32) * 4
        // this fomula is from BMP file structure on wiki pedia
        // we will overwrite the RowSize variable instead of creating new one.
        // if RowSize was a multiple of 4 bytes it will keep the data. otherwise it will be changed here.        
        RowSize = (bpp * Width + 31) / 32;          // in the RowSize Variable only the integer part will be saved, the number after the point will be discarded.
        RowSize = RowSize * 4;                      // then the integer part will be multiplied by 4 to make to a multiple of 4 bytes.

        // that is all you need to make.
        printf("is not a multiple of 4 bytes");
    }

    // now we need to calculate the PixelArraySize in order to allocate memory for our image.
    // therefore we use the formula provided by the BMP File Structure.

    PixelArraySize = RowSize * absolute(Height);            // sometimes the image height might be expressed in negative number so we need to pass it through absolute value function.
                                                                // if the image height is negative then it means the image is stored in top-down format.
    

    // now do swap the colors because they are stored in the form of BGR, therefore we need to change it to RGB

    // Swapping color values to RGB from BGR
    if(isSwapped == 0) {
        for(int i = Height; i > 0; i--) {
            for(int j = 0; j < RowSize; j+=3) {
                tempColor = PixelData[(i*RowSize+j)];
                PixelData[(i*RowSize+j)] = PixelData[(i*RowSize+j) + 2];
                PixelData[(i*RowSize+j) + 2] = tempColor;
            }
        }
        isSwapped = 1;
    }

    if(Height > 0)
        flip_image_array(PixelData, Width, Height);


    for(int i = Height - i; i > 0; i--) {
        for(int j = 0; j < Width; j++) {
            int kk = 3 * j;

            red = PixelData[Height-i*RowSize+kk];
            green = PixelData[(Height-i*RowSize+kk) + 1];
            blue = PixelData[(Height-i*RowSize+kk) + 2];

            colorBMP = (int)(colorBMP << 8) | red;
            colorBMP = (int)(colorBMP << 8) | green;
            colorBMP = (int)(colorBMP << 8) | blue;
            PutPixel(j + x, i + y, colorBMP);
        }
    }
}

void RotateImage() {}