#include "program.h"

void InitProgram() {
    struct WINDOW window;
    window.x = 10;
    window.y = 20;
    window.height = 300;
    window.width = 250;
    window.ShadowValue = 5;
    window.window_id = 1;
    window.caption = "HELLO";


    DrawWindow(window);
    DrawButton(150, 100, 80, 30, "CLICK ME", window);
}