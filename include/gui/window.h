#ifndef WINDOW_H_HEADER
#define WINDOW_H_HEADER

#include "../../include/types.h"
#include "graphics.h"

// #include "fonts.h"

typedef struct WINDOW {
    uint32_t window_id;
    uint8_t *caption;
    int x, y;
    int width, height;
    unsigned int ShadowValue;
    unsigned int BackgroundColor;
    struct RECT *rect;
    struct BITMAP *bitmap;
    struct WINDOW *child;
} WINDOW;


typedef struct RECT {
    int x, y;
    int height, width;
} RECT;

typedef struct BITMAP {
    int x, y;
    unsigned char *data;
} BITMAP;


// button structure

extern struct WINDOW Window;
extern struct RECT *Rect;
extern struct BITMAP Bitmap;
extern struct WINDOW TitleBar;
extern struct RECT Controls[3];
// extern int mouse_x;
// extern int mouse_y;

void InitWindow();
void DrawBackground(int color);
void DrawWindow(struct WINDOW w);
void DrawButton(int x, int y, int w, int h, char *text, int button_id, struct WINDOW b);
#endif