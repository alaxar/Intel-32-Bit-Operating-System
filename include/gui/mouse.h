#ifndef _MOUSE_GUI_H_
#define _MOUSE_GUI_H_

#include "../../drivers/mouse_driver/mouse_driver.h"

extern int mouse_x;
extern int mouse_y;
extern char mouse_byte[3];

int mouse_left_click();
int mouse_right_click();
int mouse_middle_click();

#endif