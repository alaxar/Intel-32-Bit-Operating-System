#include "../drivers/file_system/fat.h"
#include "../include/gui/window.h"
#include "../tools/terminal.h"
#include "../drivers/console/screen.h"
#include "../tools/tar_reader.h"

int main() {
    unsigned char A[8][8] = {
        {0,0,0,0,0,0,0,0},
        {0,0,1,1,1,0,0,0},
        {0,1,0,0,0,1,0,0},
        {0,1,0,0,0,1,0,0},
        {0,1,1,1,1,1,0,0},
        {0,1,0,0,0,1,0,0},
        {0,1,0,0,0,1,0,0},
        {0,1,0,0,0,1,0,0},
        {0,0,0,0,0,0,0,0}
    };

    unsigned char alphabets[1][9] = {
        {0x00, 0x38, 0x68, 0x68, 0x3C, 0x68, 0x68, 0x68, 0x00}
    };
    unsigned char red = 0xff;
    unsigned char green = 0x00;
    unsigned char blue = 0x00;

    get_vesa_bios_info();
    get_vesa_mode_info();
    SetupScreen();

    // pixel draw
    int color = 0x0000ff;           // RGB

    // PutPixel(512, 384, color);
// testing
    DrawBackground(color);
    // InitWindow();
    // DrawWindow(20, 20, 0, 0, "Title", 1);
    // for(int i = 0; i < 8; i++) {
    //     for(int j = 0; j < 8; j++) {
    //         if(A[i][j] == 1) {
    //             PutPixel(Rect.x+j, Rect.y+i, 0xffffff);
    //         }
    //     }
    // }
    // FillRect(10, 10, 300, 200, color);
    clear_screen();
    terminal_init();
    ReadTarFile("zap-ext-light18.psf");
    while(1);
}