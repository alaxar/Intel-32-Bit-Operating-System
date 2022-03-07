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

    Context *context;
} Window;

Window *Window_new(uint16_t x, uint16_t y, uint16_t width, uint16_t height, Context *context);
void DrawWindow(Window *window);
void Context_fillRect(Context *context, uint32_t x, uint32_t y, uint32_t width, uint32_t height, uint32_t color);

#endif