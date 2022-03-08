#include "screen.h"

struct SCREEN_DIMENSION scrn_dim;
PixelOffset;

unsigned char *backbuffer;

void SetupScreen() {
    // getting vesa information
    get_vesa_bios_info();
    get_vesa_mode_info();
    backbuffer = (unsigned char*)page_allocator(scrn_dim.ScreenHeight * scrn_dim.ScreenWidth);
    scrn_dim.ScreenWidth = vbe_mode->width;         // width
    scrn_dim.ScreenHeight = vbe_mode->height;       // height
    scrn_dim.PixelWidth = vbe_mode->bpp / 8;        // bits per pixel
    scrn_dim.ScreenPitch = vbe_mode->pitch;         // pitch how many bytes are need to the right to reach the next row width*Bpp
    scrn_dim.pixel = vbe_mode->framebuffer;         // linear framebuffer.
}

void PutPixel(int x, int y, int color) {
    PixelOffset = y * scrn_dim.ScreenPitch + x * scrn_dim.PixelWidth;       // offset
    backbuffer[PixelOffset] = color & 0xFF;             // Blue.
    backbuffer[PixelOffset + 1] = (color >> 8) & 0xFF;  // Green.
    backbuffer[PixelOffset + 2] = (color >> 16) & 0xFF; // Red.
}

void FillRect(int x, int y, int width, int height, int color) {
    for(int i = 0; i < height; i++) {
        for(int j = 0; j < width; j++) {
            PixelOffset = (y + i) * scrn_dim.ScreenPitch + (x + j) * scrn_dim.PixelWidth;
            backbuffer[PixelOffset] = color & 0xFF;
            backbuffer[PixelOffset + 1] = (color >> 8) & 0xFF;
            backbuffer[PixelOffset + 2] = (color >> 16) & 0xFF;
        }
    }   
}

void swap_buffer() {
    memory_copy(backbuffer, scrn_dim.pixel, (scrn_dim.ScreenHeight * scrn_dim.ScreenPitch));
}

void UpdateScreen() {
    #ifdef VERTICAL_RETRACE
        while((port_byte_in(0x3DA) & 0x08));
        while(!(port_byte_in(0x3DA) & 0x08));
    #endif
    swap_buffer();
}