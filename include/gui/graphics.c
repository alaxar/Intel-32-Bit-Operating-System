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