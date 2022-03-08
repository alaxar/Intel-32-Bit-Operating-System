#include "calculator.h"


Window calcWin = {50, 100, 600, 400};
Window Dialog = {25, 25, 320, 100};

void InitCalculator() {
    // main window
    calcWin.caption = "CALCULATOR";
    calcWin.ShadowValue = 5;

    // dialog window
    Dialog.caption = "INFORMATION";
    Dialog.ShadowValue = 5;

    // window draw
    DrawWindow(&calcWin);

    addEvent(1, &Calculate);
    DrawButton(10, 10, 30, 90, "CALCULATE", 1, &calcWin);

    addEvent(2, &exit);
    DrawButton(150, 10, 30, 90, "EXIT", 2, &calcWin);

}

void Calculate() {
    DrawWindow(&Dialog);
    DrawButton(320 / 3, 100 / 3, 30, 100, "CALCULATING", 3, &Dialog);
}

void exit() {
    DrawWindow(&Dialog);
    DrawText(Dialog.x + 10, Dialog.y + 50, "ARE YOU SURE YOU WANT TO EXIT");
}

int sum(int x, int y) {

}

int mul(int x, int y) {

}

int sub(int x, int y) {

}