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
    int isCalled = 0;

void redraw_desktop_interrupt() {
    int backgroundColor = 0x159c49;           // RGB
    // DrawBackground(backgroundColor);
        for(int i = 0; i < scrn_dim.ScreenHeight; i++) {
            for(int j = 0; j < scrn_dim.ScreenWidth; j++) {
                PutPixel(j, i, backgroundColor);
            }
        }
    PaintDesktop(desktop);
    DrawRectangle(mouse_x, mouse_y, 10, 10, 0xffffff);
    // UpdateScreen();
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
    New_window(&desktop, 41, 0, 10, 320, 200, 0xff0000, "FIRST WINDOW");           // red
    New_window(&desktop, 42, 300, 100, 320, 200, 0x00ff00, "SECOND WINDOW");          // green
    New_window(&desktop, 43, 350, 30, 320, 200, 0x0000ff, "THRID WINDOW");          // blue
    New_window(&desktop, 44, 400, 200, 320, 200, 0xffff00, "FOURTH WINDOW");          // other color

    PaintDesktop(desktop);
    // UpdateScreen();
    while(1); // hang the cpu here
}