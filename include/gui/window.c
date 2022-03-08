#include "window.h"

Window Controls[3];
Window TitleBar;
// Mouse clicks
int LeftClick = 0;
int RightClick = 0;
int MiddleClick = 0;
void (*callback)() = 0;

void DrawWindow(Window *window) {
    // declaration

    // Draw Shadow for window
    // shadow must be drawn befor the window to eliminate over drawing
    FillRect(window->x + window->ShadowValue, window->y + window->ShadowValue, window->width, window->height, 0x39463e);

    // Draw Window
    // DrawRectangle(window->x, window->y, window->height, window->width, 0xff00ff);
    FillRect(window->x, window->y, window->width, window->height, 0xbda267);


    // titlebar
    TitleBar.x = window->x;
    TitleBar.y = window->y;
    TitleBar.width = window->x + window->width;
    TitleBar.height = 25;

    // DrawRectangle(window->x, window->y, TitleBar.height, window->width, 0x00ffff);
    FillRect(window->x, window->y, window->width, TitleBar.height, 0x32503c);

    // window movement
    int x, y;
    LeftClick = mouse_left_click();
    if((mouse_x > window->x && mouse_x < window->x + window->width - (25 * 3)) && (mouse_y > window->y && mouse_y < window->y + TitleBar.height)) {
        if(LeftClick == 1) {
            window->x = mouse_x - (window->width / 3);
            window->y = mouse_y - 5;
        }
    }

    // title
    DrawText(window->x + 10, window->y + 9, window->caption);

    // Controls
    // close
    int width = 25, ControlResizeResolution = 10, ControlResizeCoordinate = TitleBar.height / 5;
    Controls[0].x = window->x + window->width - width;
    Controls[0].y = window->y + ControlResizeCoordinate;
    Controls[0].width = width - ControlResizeResolution;
    Controls[0].height = TitleBar.height - ControlResizeResolution;

    // maximize
    Controls[1].x = window->x + window->width - width * 2;
    Controls[1].y = window->y + ControlResizeCoordinate;
    Controls[1].width = width - ControlResizeResolution;
    Controls[1].height = TitleBar.height - ControlResizeResolution;

    //minimize
    Controls[2].x = window->x + window->width - width * 3;
    Controls[2].y = window->y + ControlResizeCoordinate;
    Controls[2].width = width - ControlResizeResolution;
    Controls[2].height = TitleBar.height - ControlResizeResolution;

    FillRect(Controls[0].x, Controls[0].y, Controls[0].width, Controls[0].height, 0xff0000);
    FillRect(Controls[1].x, Controls[1].y, Controls[1].width, Controls[1].height, 0xffff00);
    FillRect(Controls[2].x, Controls[2].y, Controls[2].width, Controls[2].height, 0x00ff00);

    // controls mouse control
    if((mouse_x > Controls[0].x && mouse_x < Controls[0].x + Controls[0].width) && (mouse_y > Controls[0].y && mouse_y <  Controls[0].y + Controls[0].height)) {
        DrawRectangle(Controls[0].x, Controls[0].y, Controls[0].height, Controls[0].width, 0xffffff);
        LeftClick = mouse_left_click();
        if(LeftClick == 1) {
            DrawRectangle(Controls[0].x + 1, Controls[0].y + 1, Controls[0].height, Controls[0].width, 0xff0000);
        }
    } 

    if((mouse_x > Controls[1].x && mouse_x < Controls[1].x + Controls[1].width) && (mouse_y > Controls[1].y && mouse_y < Controls[1].y + Controls[1].height)) {
        DrawRectangle(Controls[1].x, Controls[1].y, Controls[1].height, Controls[1].width, 0xffffff);
        if(LeftClick == 1) {
            DrawRectangle(Controls[1].x + 1, Controls[1].y + 1, Controls[1].height, Controls[1].width, 0xffff00);            
        }
    } 

    if((mouse_x > Controls[2].x && mouse_x < Controls[2].x + Controls[2].width) && (mouse_y > Controls[2].y && mouse_y < Controls[2].y + Controls[2].height)) {
        DrawRectangle(Controls[2].x, Controls[2].y, Controls[2].height, Controls[2].width, 0xffffff);
        if(LeftClick == 1) {
            DrawRectangle(Controls[2].x + 1, Controls[2].y + 1, Controls[2].height, Controls[2].width, 0x00ff00);            
        }
    }
}

void DrawButton(int x, int y, int h, int w, char *text, int button_id, Window *window) {


    // button coordincates
    int ButtonX = window->x + x;
    int ButtonY = window->y + TitleBar.height + y;
    // DrawRectangle(ButtonX, ButtonY, h, w, 0x00aaff);
    FillRect(ButtonX, ButtonY, w, h, 0x32503c);
    DrawText((window->x + x) + 10, (window->y + TitleBar.height + y) + 10 , text);

    // check if the mouse coordinate is the hovering over the a button
    if((mouse_x > ButtonX && mouse_x < ButtonX + w) && (mouse_y > ButtonY && mouse_y < ButtonY + h)) {
        // the hover effect.
        DrawRectangle(ButtonX, ButtonY, h, w, 0xffffff);
        // check if there is a click
        // if there is a click then see if the button is event triggred.
        LeftClick = mouse_left_click();
        if(LeftClick == 1) {
            DrawRectangle(ButtonX + 1, ButtonY + 1, h, w, 0xffffff);
            callback = search(button_id);
            if(callback != 0) {
                callback();
            }
        }
    }
}

void DrawBackground(int color) {
    for(int y = 0; y < scrn_dim.ScreenHeight; y++) {
        for(int x = 0; x < scrn_dim.ScreenWidth; x++) {
            PutPixel(x, y, color);
        }
    }
}