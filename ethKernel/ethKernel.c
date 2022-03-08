#include "../drivers/file_system/fat.h"
#include "../include/gui/gui.h"
#include "../tools/terminal.h"
#include "../drivers/console/screen.h"
#include "../tools/tar_reader.h"
#include "memory_mgr/memory_mgr.h"

struct node {
    int data;
    struct node *next;
};

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

    while(1) {          // game loop
        DrawBackground(backgroundColor);
        InitCalculator();
        DrawRectangle(mouse_x, mouse_y, 10, 10, 0xffffff);
        UpdateScreen();
    }
}
