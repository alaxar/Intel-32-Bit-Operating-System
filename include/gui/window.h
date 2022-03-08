#ifndef WINDOW_H_HEADER
#define WINDOW_H_HEADER

#include "../../include/types.h"
#include "mouse.h"
#include "graphics.h"
#include "event_handling/event_handler.h"

// #include "fonts.h"
typedef struct Context_struct {
    uint32_t    *buffer;
    unsigned int width;
    unsigned int height;
} Context;

typedef struct window_struct {
    uint16_t x;
    uint16_t y;
    uint16_t width;
    uint16_t height;
    uint8_t isAllocated;
    uint8_t *caption;
    uint8_t ShadowValue;

    // nodes
    Context *context;
    struct Window *prev, *next;
    struct Window *child;
} Window;

void DrawWindow(Window *w);
void DrawBackground(int color);
void DrawButton(int x, int y, int h, int w, char *text, int button_id, Window *window);
#endif