#include "window.h"

struct RECT *Rect;
struct WINDOW Window;
struct WINDOW TitleBar;
struct RECT Controls[3];        // close, maximize, minimize
struct BITMAP Bitmap;
struct WINDOW Button;

extern int mouse_x;
extern int mouse_y;
extern char mouse_byte[3];
int LeftClick = 0;
int RightClick = 0;
int MiddleClick = 0;

void InitWindow() {
    // default window values.
    // Setting up the RECT    

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
    Window.child = &TitleBar;

    // setting up bitmap struct
    Bitmap.x = Rect->x;
    Bitmap.y = Rect->y;
}

void DrawWindow(struct WINDOW w) {

    // if title is not given give the default
    if(w.caption == NULL)
        w.caption = "UNTITLED WINDOW";

    InitWindow();

    // Draw Window Shadow
    FillRect(Rect->x + w.ShadowValue, Rect->y + w.ShadowValue, Rect->width, Rect->height, 0x39463e);

    // Draw window
    FillRect(Rect->x, Rect->y, Rect->width, Rect->height, 0xbda267);

    // Draw Title bar
    FillRect(TitleBar.x, TitleBar.y, TitleBar.width, TitleBar.height, 0x32503c);
    DrawText(TitleBar.x + 8, TitleBar.y + 8, w.caption);

    // // Draw Controls (close, maximize, minimize respectively)
    FillRect(Controls[0].x, Controls[0].y, Controls[0].width, Controls[0].height, 0xff0000);
    FillRect(Controls[1].x, Controls[1].y, Controls[1].width, Controls[1].height, 0xffff00);
    FillRect(Controls[2].x, Controls[2].y, Controls[2].width, Controls[2].height, 0x00ff00);


    // mouse control for window controls
    int x, y;
    LeftClick = mouse_left_click();
    if((mouse_x > TitleBar.x && mouse_x < TitleBar.x + TitleBar.width) && (mouse_y > TitleBar.y  && mouse_y < TitleBar.y + 25)) {
        if(LeftClick == 1) {
            Rect->x = mouse_x - (Rect->width / 2) + 60;
            Rect->y = mouse_y - 8;
        }
    }
}

void DrawButton(int x, int y, int w, int h, char* text, int button_id, struct WINDOW b) {
    // InitWindow();
    if(x > Rect->x + Rect->width)
        x = Rect->x;
    if(y > Rect->y + Rect->height)
        y = Rect->y + TitleBar.height;

    // button coordincates
    int ButtonX = Rect->x + x;
    int ButtonY = Rect->y + TitleBar.height + y;
    // DrawRectangle(b.x + x, b.y + TitleBar.height + y, h, w, 0xffffff);
    FillRect(ButtonX, ButtonY, w, h, 0x32503c);
    DrawText((Rect->x + x) + 10, (Rect->y + TitleBar.height + y) + 10 , text);

    // check if the mouse coordinate is the hovering over the a button
    if((mouse_x > ButtonX && mouse_x < ButtonX + w) && (mouse_y > ButtonY && mouse_y < ButtonY + h)) {
        // the hover effect.
        DrawRectangle(ButtonX, ButtonY, h, w, 0xffffff);
        // check if there is a click
        if(mouse_byte[0] & 0x1) {       // left click
            DrawRectangle(ButtonX + 1, ButtonY + 1, h, w, 0xffffff);
            // do something
        }

        if(mouse_byte[0] & 0x2) {       // right click
            DrawRectangle(ButtonX + 1, ButtonY + 1, h, w, 0xffffff);
        }

        if(mouse_byte[0] & 0x4) {       // middle click
            DrawRectangle(ButtonX, ButtonY, h, w, 0xffffff);
        }
        // if there is a click then see if the button is event triggred.
    }
}


void DrawBackground(int color) {
    for(int y = 0; y < scrn_dim.ScreenHeight; y++) {
        for(int x = 0; x < scrn_dim.ScreenWidth; x++) {
            PutPixel(x, y, color);
        }
    }
}