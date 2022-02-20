#include "screen.h"

struct SCREEN_DIMENSION scrn_dim;
int color, PixelOffset;

void SetupScreen() {
    scrn_dim.ScreenWidth = vbe_mode->width;         // width
    scrn_dim.ScreenHeight = vbe_mode->height;       // height
    scrn_dim.PixelWidth = vbe_mode->bpp / 8;        // bits per pixel
    scrn_dim.ScreenPitch = vbe_mode->pitch;         // pitch how many bytes are need to the right to reach the next row width*Bpp
    scrn_dim.pixel = vbe_mode->framebuffer;         // linear framebuffer.
}

void PutPixel(int x, int y, int color) {
    PixelOffset = y * scrn_dim.ScreenPitch + x * scrn_dim.PixelWidth;       // offset
    scrn_dim.pixel[PixelOffset] = color & 0xFF;             // Blue.
    scrn_dim.pixel[PixelOffset + 1] = (color >> 8) & 0xFF;  // Green.
    scrn_dim.pixel[PixelOffset + 2] = (color >> 16) & 0xFF; // Red.
}