#include "program.h"

void InitProgram() {
    struct WINDOW window;
    window.x = 10;
    window.y = 20;
    window.height = 300;
    window.width = 400;
    window.ShadowValue = 5;
    window.window_id = 1;
    window.caption = "PROGRAM TEST";

    DrawWindow(window);     /// PARENT WINDOW
    DrawButton(150, 100, 80, 30, "CLICK ME", window);   // CHILD WINDOW 1
    DrawButton(150, 150, 80, 30, "EXIT", window);       // CHILD WINDOW 2
}

