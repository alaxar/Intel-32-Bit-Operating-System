#include "window.h"

void Context_fillRect(Context *context, uint32_t x, uint32_t y, uint32_t width, uint32_t height, uint32_t color) {
    uint32_t cur_x;
    uint32_t max_x = x + width;
    uint32_t max_y = y + height;

    if(max_x > context->width)
        max_x = context->width;

    if(max_y > context->height)
        max_y = context->height;

    for (; y < max_y; y++)
        for(; x <max_x; x++)
            PutPixel(x, y, color);

}

Window *Window_new(uint16_t x, uint16_t y, uint16_t width, uint16_t height, Context *context) {
    // allocate memory for window struct
    // Window windoww;
    Window window;
    // if(!(window = (struct Window*)page_allocator(sizeof(Window))))
        // return window;

    // printf(itoa((int)window), -1, -1, 0);
    window.x = x;
    window.y = y;
    window.height = height;
    window.width = width;
    window.context = context;

    return &window;
}

void DrawWindow(Window *window) {
    Context_fillRect(window->context, window->x, window->y, window->width, window->height, 0xffffff);
}