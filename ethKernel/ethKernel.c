#include "../drivers/file_system/fat.h"
#include "../include/gui/gui.h"
#include "../tools/terminal.h"
#include "../drivers/console/screen.h"
#include "../tools/tar_reader.h"
#include "memory_mgr/memory_mgr.h"
#include "multiboot/multiboot.h"
#include "../include/gui/bmp.h"
#include "../include/gui/window_system/window.h"

multiboot_info_t *mbi;
Window *desktop = NULL;
extern char mouse_byte[3];

void redraw_desktop_interrupt() {
    // DrawBackground(0xfafafa);
    Remove_window_to_end(&desktop, 1);
    PaintDesktop(desktop);
    DrawRectangle(mouse_x, mouse_y, 10, 10, 0xffffff);
    UpdateScreen();
}

int main(unsigned long address, unsigned long grub_magic) {
    // // setup multiboot header
    mbi = (multiboot_info_t*)address;

    gdt_install();
    idt_install();      // interrupt install
    isrs_install();    
    irq_install();
    keyboard_install();
    mouse_install();
    enable_interrupts();
    clear_screen();
    terminal_init();
    SetupScreen(mbi);
    int backgroundColor = 0x159c49;           // RGB
 
    New_window(&desktop, 0, 10, 20, 320, 200, 0xff0000, "title");           // red
    New_window(&desktop, 1, 300, 100, 320, 200, 0x00ff00, "title");          // green
    New_window(&desktop, 2, 350, 30, 320, 200, 0x0000ff, "title");          // blue
    New_window(&desktop, 3, 350, 400, 320, 200, 0xffff00, "title");          // other color

    PaintDesktop(desktop);
    UpdateScreen();
    while(1); // hang the cpu here
}