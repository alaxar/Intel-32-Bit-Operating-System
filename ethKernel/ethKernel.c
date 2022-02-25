#include "../drivers/file_system/fat.h"
#include "../include/gui/window.h"
#include "../tools/terminal.h"
#include "../drivers/console/screen.h"
#include "../tools/tar_reader.h"

int main() {
    clear_screen();
    terminal_init();
    get_vesa_bios_info();
    get_vesa_mode_info();
    SetupScreen();

    int color = 0x159c49;           // RGB

    DrawBackground(color);
    DrawWindow(30, 30, 0, 0, 5, "Title", 1);


    printf(itoa(Rect->x), -1, -1, 0);
    ReadTarFile("zap-ext-light18.psf");
    while(1);
}