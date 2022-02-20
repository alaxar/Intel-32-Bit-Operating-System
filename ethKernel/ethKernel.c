#include "../include/gui/screen.h"

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

    unsigned char red = 0xff;
    unsigned char green = 0x00;
    unsigned char blue = 0x00;

    get_vesa_bios_info();
    get_vesa_mode_info();
    SetupScreen();

    // pixel draw
    int color = 0xd2e6ef;           // RGB
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            if(A[i][j] == 1) {
                PutPixel(j, i, color);
            }
        }
    }

    FillRect(10, 10, 100, 100, color);
    while(1);
}