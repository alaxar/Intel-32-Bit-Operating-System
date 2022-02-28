#ifndef _GRAPHICS_H_
#define _GRAPHICS_H_

#include "screen.h"
#include "../math.h"

// color Definitions
#define WHITE 0xffffff
#define BLACK 0xffffff
#define GREEN 0x00ff00
#define BLUE  0x0000ff
#define RED   0xff0000


void DrawRectangle(int x, int y, int height, int width, int color);
void DrawCircle(int x, int y, int radius);
void DrawLine(int x1, int y1, int x2, int y2, int color);

#endif