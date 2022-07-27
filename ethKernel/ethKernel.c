#include "../drivers/file_system/fat.h"
#include "../include/gui/gui.h"
#include "../tools/terminal.h"
#include "../drivers/console/screen.h"
#include "../tools/tar_reader.h"
#include "memory_mgr/memory_mgr.h"
#include "multiboot/multiboot.h"
#include "../include/gui/bmp.h"
#include "../include/gui/window_system/window.h"
#include "../include/gui/font/fonts.h"

multiboot_info_t *mbi;
extern char mouse_byte[3];
int isCalled = 0;
// DIB *dib_header;
Window desktop = {0, 0, 0, 800, 600, 0x0e387a, "DESKTOP", 0};
Window win1 = {1, 50, 50, 420, 320, 0xffffffff, "TERMINAL", 0};
Window win2 = {2, 100, 0, 400, 400, 0xffffffff, "SYSTEM INFORMATION", 0};

void redraw_desktop_interrupt() {
    Window_paint(&desktop);
    // Window_paint(&win1);
    // Window_paint(&win2);


    // Draw Mouse
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
    if((mbi->framebuffer_width >= 320) && (mbi->framebuffer_height >= 200)) {
        SetupScreen(mbi);
    }

    // printf(itoa(mbi->mods_count), -1, -1, -1);
    Window_paint(&desktop);
    // Window_paint(&win1);
    // Window_paint(&win2);

    // Draw Mouse
    DrawRectangle(mouse_x, mouse_y, 10, 10, 0xffffff);
    UpdateScreen();

    while(1); // hang the cpu here
}