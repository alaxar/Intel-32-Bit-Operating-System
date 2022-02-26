#include "fonts.h"

struct ethiopic_font *font_header;

void DrawText(int x, int y, char *filename) {
    int i = 0;
    int index = 0;
    unsigned char *font_address;
    // convert ascii to bitmap font
    
    do {
        index = filename[i];
        index = index - 65;
        i++;
    } while(filename[i] != '\0');
    



    // get the address of the loaded font from memory using tar file system.
    font_address = FindFileTAR("font.ef");


    font_header = (struct ethiopic_font*)font_address;

    for(int i = 0; i < font_header->height; i++) {
        for(int j = 0; j < font_header->width; j++) {
            if(*(font_address+font_header->offset+(index*8)+i) & (128 >> j)) {
                PutPixel(j+x, i+y, 0xffffff);
            }
        }
    }
}