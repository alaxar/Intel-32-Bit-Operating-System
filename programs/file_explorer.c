#include "file_explorer.h"

Window win1 = {20, 20, 320, 200, 0};
Window win2 = {400, 300, 320, 200, 0};
Window win3 = {400, 0, 320, 200, 0};

void test() {
    DrawText(300, 0, "YOU CLICKED ME");
}

void exit() {
    DrawText(300, 0, "EXIT");
}

void InitFileExplorer() {
    win1.caption = "FILE EXPLORER";
    win1.ShadowValue = 5;
    win2.caption = "CALCULATOR";
    win2.ShadowValue = 5;
    win3.caption = "CALENDAR";
    win3.ShadowValue = 5;
    DrawWindow(&win1);
    addEvent(1, &test);
    DrawButton(10, 10, 30, 80, "EXPLORE", 1, &win1);
    addEvent(2, &exit);
    DrawButton(100, 10, 30, 80, "EXIT", 2, &win1);

    // DrawWindow(&win2);
    // DrawButton(10, 10, 30, 90, "CALCULATE", 1, &win2);
    // DrawButton(110, 10, 30, 80, "EXIT", 1, &win2);
    // DrawWindow(&win3);
    // DrawButton(10, 10, 30, 80, "SHOW", 2, &win3);
    // DrawButton(100, 10, 30, 80, "EXIT", 3, &win3);
}

