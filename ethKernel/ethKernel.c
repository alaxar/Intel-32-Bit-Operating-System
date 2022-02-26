#include "../drivers/file_system/fat.h"
#include "../include/gui/window.h"
#include "../tools/terminal.h"
#include "../drivers/console/screen.h"
#include "../tools/tar_reader.h"

unsigned char fontA[8] = {0x3c,0x7e,0xc3,0xc3,0xff,0xff,0xc3,0xc3};

int main() {
    idt_install();
    isrs_install();
    irq_install();
    keyboard_install();
    enable_interrupts();
    clear_screen();
    terminal_init();
    get_vesa_bios_info();
    get_vesa_mode_info();
    SetupScreen();

    int color = 0x159c49;           // RGB

    // DrawBackground(color);
    // DrawWindow(30, 30, 0, 0, 5, "Title", 1);

    DrawText(20, 20, "A");
    while(1);
}