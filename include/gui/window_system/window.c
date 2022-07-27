#include "window.h"
#include "../bmp.h"

Window Controls[2];
Window startButton = {3, 10, 10, 50, 25, 0x343148, "MENU"};
DIB *dib_header;

void CreateTaskbar(Window *window) {
    FillRect(window->x, window->y, window->width, 40, 0xc0c0c0);
    CreateButton(window, &startButton);
}

void CreateDesktop(Window *window) {
    dib_header = ReadBMP("background.bmp");
    DrawImage(0, 0, dib_header);
    // FillRect(window->x, window->y, scrn_dim.ScreenWidth, scrn_dim.ScreenHeight, 0x177b4d);
}

void CreateButton(Window *parent, Window *button) {
    FillRect(parent->x + button->x, parent->x + button->y, button->width, button->height, 0x343148);
    // DrawText(parent->x + button->x, parent->y + button->y, button->title);
    if((mouse_x > parent->x + button->x && mouse_x < parent->x + button->x + button->width) && (mouse_y > parent->y + button->y && mouse_y < parent->y + button->y + button->height)) {
        DrawRectangle(parent->x + button->x, parent->y + button->y, button->height, button->width, 0xffffff);
    }
    DrawText(parent->x + button->x + 10, parent->y + button->y + 10, button->title);
}

void Window_paint(Window *window) {
    if(window->window_id == 0) {
        CreateDesktop(window);
        CreateTaskbar(window);
    } else {
        // shadow
        FillRect(window->x + 10, window->y + 10, window->width, window->height, 0x7b7a72);

        // body
        FillRect(window->x, window->y, window->width, window->height, 0xD7C49E);

        // inner body
        FillRect(window->x + 5, window->y + 45, window->width - 10, (window->height - 50), 0x808080);

        // cursor
        FillRect(window->x + 15, window->y + 50, 6, 25, 0xd0d0d0);

        // title bar
        FillRect(window->x, window->y, window->width, 30, 0x343148);

        // title
        DrawText(window->x + 10, window->y + 5, window->title);
        // controls
        // Maximiza
        Controls[0].x = window->x + window->width - 35;
        Controls[0].y = window->y + 7;
        Controls[0].width = 18;
        Controls[0].height = 18;
        Controls[0].color = 0xD7C49E;

        // Minmize
        Controls[1].x = window->x + window->width - (35 + 35);
        Controls[1].y = window->y + 7;
        Controls[1].width = 18;
        Controls[1].height = 18;
        Controls[1].color = 0xD7C49E;


        // Draw controls
        FillRect(Controls[0].x, Controls[0].y, Controls[0].width, Controls[0].height, Controls[0].color);
        FillRect(Controls[1].x, Controls[1].y, Controls[1].width, Controls[1].height, Controls[1].color);

        if((mouse_x > Controls[0].x && mouse_x < Controls[0].x + Controls[0].width) && (mouse_y > Controls[0].y && mouse_y < Controls[0].y + Controls[0].width)) {
            DrawRectangle(Controls[0].x, Controls[0].y, Controls[0].height, Controls[0].width, 0xfffffff);
            if(mouse_left_click()) {
                window->x = window->x + 100;
                window->y = window->y;
                window->width = 100;
                window->height = 25;
                window->old_height = window->height;
                window->old_width = window->width;
                window->old_x = window->x;
                window->old_y = window->y;
            }
        }

        if((mouse_x > Controls[1].x && mouse_x < Controls[1].x + Controls[1].width) && (mouse_y > Controls[1].y && mouse_y < Controls[1].y + Controls[1].width)) {
            DrawRectangle(Controls[1].x, Controls[1].y, Controls[1].height, Controls[1].width, 0xfffffff);
            if(mouse_left_click()) {
                if(window->isMinimized == 0) {
                    window->x = window->x + 100;
                    window->y = window->y;
                    window->width = 150;
                    window->height = 25;
                    window->old_height = window->height;
                    window->old_width = window->width;
                    window->old_x = window->x;
                    window->old_y = window->y;
                    window->isMinimized = 1;
                } else {
                    window->x = window->old_x;
                    window->y = window->old_y;
                    window->width = window->old_width;
                    window->height = window->old_height;
                    window->isMinimized = 0;
                }
            }
        }

        // movement
        if((mouse_x > window->x && mouse_x < window->x + window->width) && (mouse_y > window->y && mouse_y < window->y + window->height)) {
            if(mouse_left_click()) {
                window->x = mouse_x - (window->width / 2);
                window->y = mouse_y - (35 / 2);
            }
        }
    }
}