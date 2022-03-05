#include "mouse.h"

extern int mouse_x;
extern int mouse_y;
extern char mouse_byte[3];

int mouse_left_click() {
    if(mouse_byte[0] & 0x1 == 0x1) {
        return 1;       // if left click then return one.
    }
}
int mouse_right_click() {
    if(mouse_byte[0] & 0x2 == 0x2) {
        return 1;
    }

}
int mouse_middle_click() {
    if(mouse_byte[0] & 0x4 == 0x4) {
        return 1;
    }
}