#ifndef _FONTS_HEADER
#define _FONTS_HEADER
// Font handler

#include "../../../include/types.h"

typedef struct ethiopic_font {
    unsigned char magic[2];
    unsigned char offset;
    unsigned char width;
    unsigned char height;
} __attribute__((packed)) ethiopic_font;

extern struct ethiopic_font *font_header;

void DrawText(int x, int y, char *filename);

#endif