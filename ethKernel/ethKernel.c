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

    // linked list test
    insert(0, 12);
    insert(1, 20);
    insert(2, 50);

    int value = search(0);

    if(value == -1)
        printf("key not found", -1, -1, 0);
    else
        printf(itoa(value), -1, -1, 0);
}
