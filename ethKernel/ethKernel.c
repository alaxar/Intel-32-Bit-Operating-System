#include "../drivers/file_system/fat.h"
#include "../include/gui/gui.h"
#include "../tools/terminal.h"
#include "../drivers/console/screen.h"
#include "../tools/tar_reader.h"


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
    while(1) {
        DrawBackground(color);
        InitFileExplorer();
        DrawRectangle(mouse_x, mouse_y, 10, 10, 0xffffff);        
        swap_buffer();
    }
    while(1);
}