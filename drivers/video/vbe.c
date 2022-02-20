#include "vbe.h"

unsigned short *vesa_info_addr;
unsigned short *vesa_mode_addr;
int width, height, pitch, pixelwidth;
unsigned char *pixel;

struct vbe_mode_info_structure *vbe_mode;
struct vbe_info_structure *vbe_info;

void get_info() {

    get_vesa_bios_info();
    get_vesa_mode_info();
}

int get_vesa_bios_info() {
    vesa_info_addr = (unsigned short *)0x2000;
    vbe_info = (struct vbe_info_structure*)vesa_info_addr;

    // if(vbe_info == NULL)
        // return -1;

    if(vbe_info->version == 0x200) {
        // __asm__("hlt");
    }
}

int get_vesa_mode_info() {
    vesa_mode_addr = (unsigned short *)0x2100;
    vbe_mode = (struct vbe_mode_info_structure *)vesa_mode_addr;

    if(vbe_mode == NULL)
        return -1;

    if(vbe_mode->pitch == 1024*3) {
        // __asm__("hlt");

    }

        pixel = (unsigned char*)vbe_mode->framebuffer;
        width = vbe_mode->width;
        pitch = vbe_mode->pitch;
        pixelwidth = vbe_mode->bpp / 8;
}