#include "graphics.h"

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

void DrawLine(int x1, int y1, int x2, int y2, int color) {
    // DDA Line drawing algorithm
    int dx, dy, steps, x, y;
    int XIncrement, YIncrement;

    dx = x2 - x1;
    dy = y2 - y1;

    if(absolute(dx) > absolute(dy))
        steps = absolute(dx);
    else
        steps = absolute(dy);

    XIncrement = dx / steps;
    YIncrement = dy / steps;

    // intial points
    x = x1;
    y = y1;

    for(int i = 0; i < steps; i++) {
        PutPixel(x, y, color);
        x = x + XIncrement;
        y = y + YIncrement;
    }
}

void DrawCircle(int x, int y, int radius) {
    
}