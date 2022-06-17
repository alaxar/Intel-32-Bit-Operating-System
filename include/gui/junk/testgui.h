#pragma once
#include "../types.h"

typedef struct ListNode_struct {
    void* payload;
    struct ListNode_struct* prev;
    struct ListNode_struct* next;
} ListNode;

typedef struct List_struct {
    unsigned int count; 
    ListNode* root_node;
} List;

typedef struct Context_struct {  
    uint32_t* buffer; //A pointer to our framebuffer
    uint16_t width; //The dimensions of the framebuffer
    uint16_t height; 
    List* clip_rects;
} Context;


//A type to encapsulate a basic dynamic list


typedef struct Window_struct {  
    uint16_t x;
    uint16_t y;
    uint16_t width;
    uint16_t height;
    uint32_t fill_color;
    Context* context;
} Window;

typedef struct Desktop_struct {
    List* children;
    Context* context;
    uint8_t last_button_state;
    uint16_t mouse_x;
    uint16_t mouse_y;
    Window* drag_child;
    uint16_t drag_off_x;
    uint16_t drag_off_y;
} Desktop;

// It'll have the obious properties
typedef struct Rect_struct {
    int top;
    int left;
    int bottom;
    int right;
} Rect;


List* List_new();
int List_add(List* list, void* payload);
void* List_get_at(List* list, unsigned int index);
ListNode* ListNode_new(void* payload); 
void* List_remove_at(List* list, unsigned int index);
void Desktop_process_mouse(Desktop *desktop, unsigned short mouse_x, unsigned short mouse_y, unsigned char mouse_buttons);
Window* Window_new(uint16_t x, uint16_t y,  
                   uint16_t width, uint16_t height, Context* context);
void Window_paint(Window* window);
Desktop* Desktop_new(Context* context);
Window* Desktop_create_window(Desktop* desktop, unsigned int x, unsigned int y,  
                              unsigned int width, unsigned int height);
void Desktop_process_mouse(Desktop* desktop, uint16_t mouse_x,
                      uint16_t mouse_y, uint8_t mouse_buttons);
void Desktop_paint(Desktop* desktop);
Rect *Rect_new(int top, int left, int bottom, int right);
List *Rect_split(Rect *subject_rect, Rect *cutting_rect);
Context *Context_new(uint16_t width, uint16_t height, uint32_t *buffer);
void Context_add_clip_rect(Context* context, Rect* added_rect);
void Context_clear_clip_rects(Context* context);
void Context_draw_rect(Context* context, int x, int y, unsigned int width, unsigned int height, uint32_t color);
void Context_horizontal_line(Context* context, int x, int y, unsigned int length, uint32_t color);
void Context_vertical_line(Context* context, int x, int y,  
                           unsigned int length, uint32_t color);