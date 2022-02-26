#include "window.h"

struct RECT *Rect;
struct WINDOW Window;
struct WINDOW TitleBar;
struct RECT Controls[3];        // close, maximize, minimize
struct BITMAP Bitmap;
struct WINDOW Button;

void InitWindow(int x, int y, int w, int h, uint32_t id) {
    // default window values.
    // Setting up the RECT    
    Rect->x = x;
    Rect->y = y;
    
    if(w < 1)
        Rect->width = (scrn_dim.ScreenWidth - 1) / 2;
    else
        Rect->width = w;

    if(h < 1)
        Rect->height = (scrn_dim.ScreenHeight - 1) / 2;
    else
        Rect->height = h;

    // setting up title bar
    TitleBar.x = Rect->x;
    TitleBar.y = Rect->y;
    TitleBar.width = Rect->width;
    TitleBar.height = 25;

    // Controls
    // close
    int width = 25, ControlResizeResolution = 10, ControlResizeCoordinate = TitleBar.height / 5;
    Controls[0].x = Rect->x + Rect->width - width;
    Controls[0].y = Rect->y + ControlResizeCoordinate;
    Controls[0].width = width - ControlResizeResolution;
    Controls[0].height = TitleBar.height - ControlResizeResolution;

    // maximize
    Controls[1].x = Rect->x + Rect->width - width * 2;
    Controls[1].y = Rect->y + ControlResizeCoordinate;
    Controls[1].width = width - ControlResizeResolution;
    Controls[1].height = TitleBar.height - ControlResizeResolution;

    //minimize
    Controls[2].x = Rect->x + Rect->width - width * 3;
    Controls[2].y = Rect->y + ControlResizeCoordinate;
    Controls[2].width = width - ControlResizeResolution;
    Controls[2].height = TitleBar.height - ControlResizeResolution;

    // setting up the window
    Window.x = Rect->x;
    Window.y = Rect->y;
    Window.height = Rect->height;
    Window.width = Rect->width;
    Window.window_id = id;
    Window.child = &TitleBar;

    // setting up bitmap struct
    Bitmap.x = Rect->x;
    Bitmap.y = Rect->y;
}

void DrawWindow(struct WINDOW w) {

    // if title is not given give the default
    if(w.caption == NULL)
        w.caption = "UNTITLED WINDOW";

    InitWindow(w.x, w.y, w.width, w.height, w.window_id);

    // Draw Window Shadow
    // DrawRectangle(Rect->x + ShadowValue, Rect->y + ShadowValue, Rect->height, Rect->width, 0x000000);
    FillRect(Rect->x + w.ShadowValue, Rect->y + w.ShadowValue, Rect->width, Rect->height, 0x39463e);

    // Draw window
    // DrawRectangle(Rect->x, Rect->y, Rect->height, Rect->width, 0x000000);
    FillRect(Rect->x, Rect->y, Rect->width, Rect->height, 0xbda267);

    // Draw Title bar
    // DrawRectangle(Rect->x, Rect->y, TitleBar.height, Rect->width, 0x000000);
    FillRect(TitleBar.x, TitleBar.y, TitleBar.width, TitleBar.height, 0x32503c);
    DrawText(TitleBar.x + 8, TitleBar.y + 8, w.caption);

    // // Draw Controls
    // DrawRectangle(Controls[0].x, Rect->y, Controls[0].height, Controls[0].width, 0x000000);
    // DrawRectangle(Controls[1].x, Rect->y, Controls[1].height, Controls[1].width, 0x000000);
    // DrawRectangle(Controls[2].x, Rect->y, Controls[2].height, Controls[2].width, 0x000000);

    // filling 
    FillRect(Controls[0].x, Controls[0].y, Controls[0].width, Controls[0].height, 0xff0000);
    FillRect(Controls[1].x, Controls[1].y, Controls[1].width, Controls[1].height, 0xffff00);
    FillRect(Controls[2].x, Controls[2].y, Controls[2].width, Controls[2].height, 0x00ff00);

}

void DrawButton(int x, int y, int w, int h, char* text, struct WINDOW b) {
    if(x > b.x + b.width)
        x = b.x;
    if(y > b.y + b.height)
        y = b.y + TitleBar.height;

    // DrawRectangle(b.x + x, b.y + TitleBar.height + y, h, w, 0xffffff);
    FillRect(b.x + x, b.y + TitleBar.height + y, w, h, 0x32503c);
    DrawText((b.x + x) + 10, (b.y + TitleBar.height + y) + 10 , text);
}

void DrawRectangle(int x, int y, int height, int width, int color) {
    int x1 = x, y1 = y;
    int x2 = x, y2 = y;
    
    for(int i = 0; i < width; i++) {
        PutPixel(x1+i, y1, color);
    }

    for(int i = 0; i < height; i++) {
        PutPixel(x1, y1+i, color);
    }


    for(int i = 0; i < width; i++) {
        PutPixel(x2+i, y1+height, color);
    }

    for(int i = 0; i < height; i++) {
        PutPixel(x2+width, y2+i, color);
    }

}

void DrawBackground(int color) {
    for(int y = 0; y < scrn_dim.ScreenHeight; y++) {
        for(int x = 0; x < scrn_dim.ScreenWidth; x++) {
            PutPixel(x, y, color);
        }
    }
}