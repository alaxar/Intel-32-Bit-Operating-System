#include "file_explorer.h"

void InitFileExplorer() {
    Context context = {scrn_dim.pixel, 1024, 768};
    // Creating windows
    Window *win1 = (Window*)Window_new(0, 0, 320, 200, &context);
    Window *win2 = (Window*)Window_new(100, 100, 500, 400, &context);

    DrawWindow(win1);
    // DrawWindow(win2);
}