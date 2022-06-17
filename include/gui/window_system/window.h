#pragma once

#include "../graphics.h"
#include "../mouse.h"
#include "../../../include/types.h"

typedef struct window_struct {
    int window_id;
    int x;
    int y;
    int width;
    int height;
    int color;
    char *title;

    // next window
    struct window_struct *next;
} Window;

void New_window(Window **desktop, int window_id, int x, int y, int width, int height, int color, char *title);
void PaintDesktop(Window *desktop);
void Remove_window(Window **desktop, int window_id);