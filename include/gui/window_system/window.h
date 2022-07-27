#pragma once

#include "../graphics.h"
#include "../mouse.h"
#include "../../../include/types.h"

extern int A1[];      // first region
extern int A2[];     // second region
extern int B1[];     // third region
extern int B2[];    // fourth region

typedef struct window_struct {
    int window_id;
    int x;
    int y;
    int width;
    int height;
    int color;
    char *title;
    int isMinimized;
    int old_x;
    int old_y;
    int old_width;
    int old_height;

    // next window
    struct window_struct *next;
} Window;

void Window_paint(Window *window);
Window *New_window(Window **window, int window_id, int x, int y, int width, int height, int color, char *title);

// Window *New_button(Window **desktop, Window *parent, int button_id, int x, int y, int width, int height, int color, char *label);
// void PaintDesktop(Window *desktop);
// void Remove_window_to_end(Window **desktop, int window_id);