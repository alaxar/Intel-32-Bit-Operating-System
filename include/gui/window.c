#include "window.h"

struct RECT Rect;
struct WINDOW Window;
struct WINDOW TitleBar;
struct RECT Controls[3];        // close, maximize, minimize
struct BITMAP Bitmap;



void InitWindow() {
    // default window values.
    // Setting up the RECT
    Rect.x = 0;
    Rect.y = 0;
    Rect.width = (scrn_dim.ScreenWidth - 1) / 2;
    Rect.height = (scrn_dim.ScreenHeight - 1) / 2;

    // setting up title bar
    TitleBar.x = Rect.x;
    TitleBar.y = Rect.y;
    TitleBar.width = Rect.width;
    TitleBar.height = 25;

    // Controls
    // close
    Controls[0].x = Rect.x;
    Controls[0].y = Rect.y;
    Controls[0].width = 25;
    Controls[0].height = TitleBar.height;
    // maximize
    Controls[1].x = Rect.x;
    Controls[1].y = Rect.y;
    Controls[1].width = 25*2;
    Controls[1].height = TitleBar.height;
    //minimize
    Controls[2].x = Rect.x;
    Controls[2].y = Rect.y;
    Controls[2].width = 25*3;
    Controls[2].height = TitleBar.height;

    // setting up the window
    Window.x = Rect.x;
    Window.y = Rect.y;
    Window.height = Rect.height;
    Window.width = Rect.width;
    Window.child = &TitleBar;

    // setting up bitmap struct
    Bitmap.x = Rect.x;
    Bitmap.y = Rect.y;
}

void DrawWindow(int x, int y, int width, int height, uint8_t *title, uint32_t window_id) {
    if(x == NULL)
        x = Rect.x;
    else
        Rect.x = x;

    if(y == NULL)
        y = Rect.y;
    else
        Rect.y = x;

    if(width == NULL)
        width = Rect.width;
    else
        Rect.width = width;

    if(height == NULL)
        height = Rect.height;
    else
        Rect.height = height;
    
    // Draw Title bar
    DrawRectangle(Rect.x, Rect.y, TitleBar.height, Rect.width, 0xFFFFFF);

    // Draw window
    DrawRectangle(Rect.x, Rect.y, Rect.height, Rect.width, 0xFFFFFF);

    // Draw Controls
    DrawRectangle(Rect.x+width-Controls[0].width, Rect.y, Controls[0].height, Controls[0].width, 0xFFFFFF);
    DrawRectangle(Rect.x+width-Controls[1].width, Rect.y, Controls[1].height, Controls[1].width, 0xFFFFFF);
    DrawRectangle(Rect.x+width-Controls[2].width, Rect.y, Controls[2].height, Controls[2].width, 0xFFFFFF);
    
}

void DrawText(int x, int y, uint8_t *text) {
    for (int i = 0; i < 1; i++)
    {
        /* code */
        for (int j = 0; j < 9; j++)
        {
            // if(alphabets[i][i] & (128 >> i)) {
                // PutPixel(j, i, 0xFFFFFF);
            // }
        }
        
    }
    
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