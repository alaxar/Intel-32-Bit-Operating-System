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
    Window *temp = desktop;
    while (temp != NULL)
    {
        // window shadow
        FillRect(temp->x + 5, temp->y + 5, temp->width, temp->height, 0x39463e);

        // title bar
        FillRect(temp->x, temp->y, temp->width, 20, 0xE2D1F9);
        DrawText(temp->x + 10, temp->y + 5, temp->title);
        // drawing window body

        FillRect(temp->x, temp->y + 20, temp->width, temp->height, 0x317773);
        DrawRectangle(temp->x, temp->y, temp->height + 20, temp->width, 0xffffff);
        if((mouse_x > temp->x && mouse_x < temp->x + temp->width) && (mouse_y > temp->y && mouse_y < temp->y + 20)) {
            if(mouse_left_click() == 1) {
                // set window focus
                for(int i = temp->window_id; i < temp->window_id + 4; i++) {
                    if(temp->window_id == i)
                        Remove_window_to_end(&desktop, i);

                // moving the windows.
                desktop->x = mouse_x - (desktop->width / 3);
                desktop->y = mouse_y - 5;
                }
                DrawRectangle(temp->x, temp->y + 20, temp->height, temp->width, 0xffffff);
            }
        }
        temp = temp->next;
    }
}

void Remove_window_to_end(Window **desktop, int window_id) {
    Window **temp_window = desktop;
    Window *last_window = *desktop;
    Window *current_window = *desktop;
    Window *prev_window = NULL;

    if(*temp_window != NULL && (*temp_window)->window_id == window_id) {
        return NULL;
    } else {
        while(current_window != NULL && current_window->window_id != window_id) {
            prev_window = current_window;
            current_window = current_window->next;
        }
    }

    // // traverse to the end of the list.
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