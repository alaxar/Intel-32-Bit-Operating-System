#include "window.h"

void New_window(Window **desktop, int window_id, int x, int y, int width, int height, int color, char *title) {
    Window *new_window = (Window*)page_allocator(sizeof(Window));
    new_window->window_id = window_id;
    new_window->x = x;
    new_window->y = y;
    new_window->width = width;
    new_window->height = height;
    new_window->title = title;
    new_window->color = color;
    new_window->next = NULL;

    Window *last_window = *desktop;

    if(*desktop == NULL) {
        *desktop = new_window;
    } else {
        while(last_window->next != NULL) {
            last_window = last_window->next;
        }
        last_window->next = new_window;
    }
}

void PaintDesktop(Window *desktop) {
    while (desktop != NULL)
    {
        // title bar
        // DrawRectangle(head->x, head->y, 20, head->width, 0xffffffff);
        FillRect(desktop->x, desktop->y, desktop->width, 20, desktop->color);
        // drawing window body
        // DrawRectangle(desktop->x, desktop->y, desktop->height, desktop->width, 0xffffffff);
        FillRect(desktop->x, desktop->y, desktop->width, desktop->height, desktop->color);
        if((mouse_x > desktop->x && mouse_x < desktop->x + desktop->width) && (mouse_y > desktop->y && mouse_y < desktop->y + desktop->height)) {
            // Remove_Window(&desktop, desktop->window_id);
            // DrawRectangle(desktop->x, desktop->y, desktop->height, desktop->window_id, 0xffffff);
        }
        desktop = desktop->next;

    }
}

void Remove_window(Window **desktop, int window_id) {
    Window *temp_window = *desktop;
    Window *last_window = *desktop;
    Window *current_window = *desktop;
    Window *prev_window = NULL;

    if(temp_window != NULL && temp_window->window_id == window_id) {
        return NULL;
    } else {
        while(current_window != NULL && current_window->window_id != window_id) {
            prev_window = current_window;
            current_window = current_window->next;
        }
    }

    // traverse to the end of the list.
    while(last_window->next != NULL) {
        last_window = last_window->next;
    }

    if(current_window->next == NULL)
        return NULL;

    prev_window->next = prev_window->next->next;
    last_window->next = current_window;
    current_window->next = NULL;
}

void DrawBackground(int color) {
    for(int i = 0; i < scrn_dim.ScreenHeight; i++) {
        for(int j = 0; j < scrn_dim.ScreenWidth; j++) {
            PutPixel(j, i, color);
        }
    }
}