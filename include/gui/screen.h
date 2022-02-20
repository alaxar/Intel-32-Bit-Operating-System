#ifndef SCREEN_H_HEADER
#define SCREEN_H_HEADER


#include "../../drivers/video/vbe.h"

typedef struct SCREEN_DIMENSION {
    int ScreenWidth;
    int ScreenHeight;
    int ScreenPitch;
    int PixelWidth;
    unsigned char *pixel;
} SCREEN_DIMENSION;

// vars
extern struct SCREEN_DIMENSION scrn_dim;
extern int color, PixelOffset;

void PutPixel(int x, int y, int color);
void SetupScreen();

#endif