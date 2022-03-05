#include "../drivers/file_system/fat.h"
#include "../include/gui/gui.h"
#include "../tools/terminal.h"
#include "../drivers/console/screen.h"
#include "../tools/tar_reader.h"
#include "memory_mgr/memory_mgr.h"

char *end_of_kernel;

int main() {
    idt_install();      // interrupt install
    isrs_install();     
    irq_install();
    keyboard_install();
    mouse_install();
    enable_interrupts();
    clear_screen();
    terminal_init();
    SetupScreen();

    int backgroundColor = 0x159c49;           // RGB
    Rect->y = 50;
    Rect->x = 50;
    while(1) {
        DrawBackground(backgroundColor);
        InitFileExplorer();
        DrawRectangle(mouse_x, mouse_y, 10, 10, 0xffffff);        
        swap_buffer();
    }
}