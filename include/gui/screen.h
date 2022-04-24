#ifndef SCREEN_H_HEADER
#define SCREEN_H_HEADER


#include "../../drivers/video/vbe.h"
#include "../../ethKernel/multiboot/multiboot.h"
typedef struct SCREEN_DIMENSION {
    int ScreenWidth;
    int ScreenHeight;
    int ScreenPitch;
    int PixelWidth;
    unsigned char *pixel;
} SCREEN_DIMENSION;

// vars
extern struct SCREEN_DIMENSION scrn_dim;
extern int PixelOffset;

void PutPixel(int x, int y, int color);
void FillRect(int x, int y, int width, int height, int color);
void SetupScreen(multiboot_info_t *mbi);

#endif