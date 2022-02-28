#include "../drivers/file_system/fat.h"
#include "../include/gui/window.h"
#include "../tools/terminal.h"
#include "../drivers/console/screen.h"
#include "../tools/tar_reader.h"


unsigned char fontA[8] = {0x3c,0x7e,0xc3,0xc3,0xff,0xff,0xc3,0xc3};
extern int mouse_x;         //signed char
extern int mouse_y;         //signed char

int main() {
    idt_install();
    isrs_install();
    irq_install();
    keyboard_install();
    mouse_install();
    enable_interrupts();
    clear_screen();
    terminal_init();
    get_vesa_bios_info();
    get_vesa_mode_info();
    SetupScreen();

    int color = 0x159c49;           // RGB
    int x= 0, y = 0;
    while(1) {
        DrawBackground(color);
        InitTest();
        DrawRectangle(mouse_x, mouse_y, 10, 10, 0xffffff);
        swap_buffer();
    }
    while(1);
}