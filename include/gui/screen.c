#include "screen.h"

struct SCREEN_DIMENSION scrn_dim;
PixelOffset;

unsigned char *backbuffer;

void SetupScreen(multiboot_info_t *mbi) {
    // getting vesa information
    get_vesa_bios_info();
    get_vesa_mode_info();
    backbuffer = (unsigned char*)page_allocator(mbi->framebuffer_height * mbi->framebuffer_width);
    scrn_dim.ScreenWidth = mbi->framebuffer_width;         // width
    scrn_dim.ScreenHeight = mbi->framebuffer_height;       // height
    scrn_dim.PixelWidth = mbi->framebuffer_bpp / 8;        // bits per pixel
    scrn_dim.ScreenPitch = mbi->framebuffer_pitch;         // pitch how many bytes are need to the right to reach the next row width*Bpp
    scrn_dim.pixel = mbi->framebuffer_addr;         // linear framebuffer.
}

void PutPixel(int x, int y, int color) {
    PixelOffset = y * scrn_dim.ScreenPitch + x * scrn_dim.PixelWidth;       // offset
    scrn_dim.pixel[PixelOffset] = color & 0xFF;             // Blue.
    scrn_dim.pixel[PixelOffset + 1] = (color >> 8) & 0xFF;  // Green.
    scrn_dim.pixel[PixelOffset + 2] = (color >> 16) & 0xFF; // Red.
}

void FillRect(int x, int y, int width, int height, int color) {
    for(int i = 0; i < height; i++) {
        for(int j = 0; j < width; j++) {
            PixelOffset = (y + i) * scrn_dim.ScreenPitch + (x + j) * scrn_dim.PixelWidth;
            scrn_dim.pixel[PixelOffset] = color & 0xFF;
            scrn_dim.pixel[PixelOffset + 1] = (color >> 8) & 0xFF;
            scrn_dim.pixel[PixelOffset + 2] = (color >> 16) & 0xFF;
        }
    }   
}

void swap_buffer() {
    // double buffer
    memory_copy(backbuffer, scrn_dim.pixel, (scrn_dim.ScreenHeight * scrn_dim.ScreenPitch));
}

void UpdateScreen() {
    #ifdef VERTICAL_RETRACE
        while((port_byte_in(0x3DA) & 0x08));
        while(!(port_byte_in(0x3DA) & 0x08));
    #endif
    swap_buffer();
}