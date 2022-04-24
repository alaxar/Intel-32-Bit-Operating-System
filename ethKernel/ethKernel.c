#include "../drivers/file_system/fat.h"
#include "../include/gui/gui.h"
#include "../tools/terminal.h"
#include "../drivers/console/screen.h"
#include "../tools/tar_reader.h"
#include "memory_mgr/memory_mgr.h"
#include "multiboot/multiboot.h"
#include "../include/gui/bmp.h"

int main(unsigned long address, unsigned long grub_magic) {
    // // setup multiboot header
    multiboot_info_t *mbi = (multiboot_info_t*)address;

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

    // if(mbi->framebuffer_addr != NULL) {
    //     printf("framebuffer is null", -1, -1, -1);
    //     PutPixel(0, 0, 0xff000000);
    // } else {
    //     printf("framebuffer is not null", -1, -1, -1);
    //     PutPixel(0, 0, 0xffffffff);
    // }

    DIB *dib = ReadBMP("sample.bmp");

    int backgroundColor = 0x159c49;           // RGB
    while(1) {
        DrawImage(0, 0, dib);
        DrawRectangle(mouse_x, mouse_y, 10, 10, 0xffffffff);
        UpdateScreen();
    }
    while(1); // hang the cpu here
}