#include "../drivers/file_system/fat.h"
#include "../include/gui/window.h"
#include "../tools/terminal.h"
#include "../drivers/console/screen.h"
#include "../tools/tar_reader.h"

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

    DrawBackground(color);
    DrawWindow(30, 30, 0, 0, 5, "Title", 1);

    printf(FindFileTAR("otherfile.txt"), -1, -1, 0);
    while(1);
}