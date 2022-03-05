#include "file_explorer.h"

struct WINDOW file_explorer;
void InitFileExplorer() {
    Rect->width = 500;
    Rect->height = 400;
    file_explorer.caption = "FILE EXPLORER";
    file_explorer.window_id = 0;
    file_explorer.ShadowValue = 5;
    file_explorer.BackgroundColor = 0xffffff;

    DrawWindow(file_explorer);
    DrawButton(50 , 50, 80, 30, "CLICK ME", 0, file_explorer);
    DrawButton(200, 50, 80, 30, "EXIT", 1, file_explorer);
}