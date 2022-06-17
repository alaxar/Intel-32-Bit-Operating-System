#include "testgui.h"

unsigned char pseudo_rand_8() {

    static unsigned short seed = 0;
    return (unsigned char)(seed = (12657 * seed + 12345) % 256);
}

//Window constructor
Window* Window_new(uint16_t x, uint16_t y,  
                   uint16_t width, uint16_t height, Context* context) {

    //Try to allocate space for a new WindowObj and fail through if page_allocator fails
    Window* window;
    if(!(window = (Window*)page_allocator(sizeof(Window))))
        return window;

    //Assign the property values
    window->x = x;
    window->y = y;
    window->width = width;
    window->height = height;
    window->context = context;

    //Moving the color assignment to the window constructor
    //so that we don't get a different color on every redraw
    window->fill_color = 0xFF000000 |            //Opacity
                         pseudo_rand_8() << 16 | //B
                         pseudo_rand_8() << 8  | //G
                         pseudo_rand_8();        //R

    return window;
}

//Method for painting a WindowObj to its context:
void Window_paint(Window* window) {

    Context_fillRect(window->context, window->x, window->y,
                     window->width, window->height, window->fill_color);
}
void Context_fillRect(Context *context, unsigned int x, unsigned int y, unsigned int width, unsigned int height, unsigned int color) {
    unsigned int cur_x;
    unsigned int max_x = x + width;
    unsigned int max_y = y + height;

    if(max_x > context->width)
        max_x = context->width;

    if(max_y > context->height)
        max_y = context->height;

    // Draw 
    for(; y < max_y; y++)
        for(cur_x = x; cur_x < max_x; cur_x++)
            context->buffer[y * context->width + cur_x] = color;
            // PutPixel(0, y, color);
}
//================| ListNode Class Implementation |================//

//Basic list constructor
List* List_new() {
    
    //page_allocator and/or fail null
    List* list;
    if(!(list = (List*)page_allocator(sizeof(List))))
        return list;

    //Fill in initial property values
    //(All we know for now is that we start out with no items) 
    list->count = 0;
    list->root_node = (ListNode*)0;

    return list;
}

//Insert a payload at the end of the list
//Zero is fail, one is success
int List_add(List* list, void* payload) {

    //Try to make a new node, exit early on fail 
    ListNode* new_node;
    if(!(new_node = ListNode_new(payload))) 
        return 0;

    //If there aren't any items in the list yet, assign the
    //new item to the root node
    if(!list->root_node) {
 
        list->root_node = new_node;        
    } else {

        //Otherwise, we'll find the last node and add our new node after it
        ListNode* current_node = list->root_node;

        //Fast forward to the end of the list 
        while(current_node->next)
            current_node = current_node->next;

        //Make the last node and first node point to each other
        current_node->next = new_node;
        new_node->prev = current_node; 
    }

    //Update the number of items in the list and return success
    list->count++;

    return 1;
}

//Get the payload of the list item at the given index
//Indices are zero-based
void* List_get_at(List* list, unsigned int index) {

    //If there's nothing in the list or we're requesting beyond the end of
    //the list, return nothing
    if(list->count == 0 || index >= list->count) 
        return (void*)0;

    //Iterate through the items in the list until we hit our index
    ListNode* current_node = list->root_node;

    //Iteration, making sure we don't hang on malformed lists
    for(unsigned int current_index = 0; (current_index < index) && current_node; current_index++)
        current_node = current_node->next;

    //Return the payload, guarding against malformed lists
    return current_node ? current_node->payload : (void*)0;
}

//Remove the item at the specified index from the list and return the item that
//was removed
//Indices are zero-based
void* List_remove_at(List* list, unsigned int index) {

    //This operates very similarly to List_get_at

    void* payload; 

    //Bounds check
    if(list->count == 0 || index >= list->count) 
        return (void*)0;

    //Iterate through the items
    ListNode* current_node = list->root_node;

    for(unsigned int current_index = 0; (current_index < index) && current_node; current_index++)
        current_node = current_node->next;

    //This is where we differ from List_get_at by stashing the payload,
    //re-pointing the current node's neighbors to each other and 
    //freeing the removed node 

    //Return early if we got a null node somehow
    if(!current_node)
        return (void*)0;

    //Stash the payload so we don't lose it when we delete the node     
    payload =  current_node->payload;
 
    //Re-point neighbors to each other 
    if(current_node->prev)
        current_node->prev->next = current_node->next;

    if(current_node->next)
        current_node->next->prev = current_node->prev;

    //If the item was the root item, we need to make
    //the node following it the new root
    if(index == 0)
        list->root_node = current_node->next;

    //Now that we've clipped the node out of the list, we must free its memory
    // free(current_node); 

    //Make sure the count of items is up-to-date
    list->count--; 

    //Finally, return the payload
    return payload;
}

//Basic listnode constructor
ListNode* ListNode_new(void* payload) {

    //page_allocator and/or fail null
    ListNode* list_node;
    if(!(list_node = (ListNode*)page_allocator(sizeof(ListNode))))
        return list_node;

    //Assign initial properties
    list_node->prev = (ListNode*)0;
    list_node->next = (ListNode*)0;
    list_node->payload = payload; 

    return list_node;
}

Desktop* Desktop_new(Context* context) {

    //page_allocator or fail 
    Desktop* desktop;
    if(!(desktop = (Desktop*)page_allocator(sizeof(Desktop))))
        return desktop;

    //Create child list or clean up and fail
    if(!(desktop->children = List_new())) {

        //Delete the new desktop object and return null 
        // free(desktop);
        return (Desktop*)0;
    }

    //Fill out other properties 
    desktop->context = context;
    desktop->last_button_state = 0;
    desktop->drag_child = (Window*)0;
    desktop->drag_off_x = 0;
    desktop->drag_off_y = 0;

    //Init mouse to the center of the screen
    desktop->mouse_x = desktop->context->width / 2;
    desktop->mouse_y = desktop->context->height / 2;

    return desktop;
}

//A method to automatically create a new window in the provided desktop 
Window* Desktop_create_window(Desktop* desktop, unsigned int x, unsigned int y,  
                          unsigned int width, unsigned int height) {

    //Attempt to create the window instance
    Window* window;
    if(!(window = Window_new(x, y, width, height, desktop->context)))
        return window;

    //Attempt to add the window to the end of the desktop's children list
    //If we fail, make sure to clean up all of our allocations so far 
    if(!List_add(desktop->children, (void*)window)) {

        // free(window);
        return (Window*)0;
    }

    return window;
}

//Interface between windowing system and mouse device
void Desktop_process_mouse(Desktop* desktop, uint16_t mouse_x,
                           uint16_t mouse_y, uint8_t mouse_buttons) {

    int i;
    Window* child;

    desktop->mouse_x = mouse_x;
    desktop->mouse_y = mouse_y;

    //Check to see if mouse button has been depressed since last mouse update
    if(mouse_buttons) {
        //Events for mouse up -> down transition
        if(!desktop->last_button_state) {

            //If we had a button depressed, then we need to see if the mouse was
            //over any of the child windows
            //We go front-to-back in terms of the window stack for free occlusion
            for(i = desktop->children->count - 1; i >= 0; i--) {

                child = (Window*)List_get_at(desktop->children, i);

                //See if the mouse position lies within the bounds of the current
                //window 
                if(mouse_x >= child->x && mouse_x < (child->x + child->width) &&
                mouse_y >= child->y && mouse_y < (child->y + child->height)) {

                    //The mouse was over this window when the mouse was pressed, so
                    //we need to raise it
                    List_remove_at(desktop->children, i); //Pull window out of list
                    List_add(desktop->children, (void*)child); //Insert at the top 

                    //We'll also set this window as the window being dragged
                    //until such a time as the mouse is released
                    desktop->drag_off_x = mouse_x - child->x;
                    desktop->drag_off_y = mouse_y - child->y;
                    desktop->drag_child = child;

                    //Since we hit a window, we can stop looking
                    break;
                }
            }
        } 
    } else {

        //If the mouse is not down, we need to make sure our drag status is cleared
        desktop->drag_child = (Window*)0;
    }

    //Update drag window to match the mouse if we have an active drag window
    if(desktop->drag_child) {

        desktop->drag_child->x = mouse_x - desktop->drag_off_x;
        desktop->drag_child->y = mouse_y - desktop->drag_off_y;
    }

    //Now that we've handled any changes the mouse may have caused, we need to
    //update the screen to reflect those changes 
    Desktop_paint(desktop);

    //Update the stored mouse button state to match the current state 
    desktop->last_button_state = mouse_buttons;
}

//Paint the desktop 
void Desktop_paint(Desktop* desktop) {
      //Loop through all of the children and call paint on each of them 
    unsigned int i;
    Window* current_window;
    Rect* temp_rect;

    //Start by clearing the desktop background
    Context_fillRect(desktop->context, 0, 0, desktop->context->width,
                      desktop->context->height, 0xFFffffff); //Change pixel format if needed 
                                                            //Currently: ABGR

    //Instead of painting the windows, for now we'll add their dimensions to the context
    //clip rects and then draw those rects to show how our splitting algorithm works
    //Clear the old rects 
    Context_clear_clip_rects(desktop->context);
    
    //Add a rect for each window
    for(i = 0; (current_window = (Window*)List_get_at(desktop->children, i)); i++) {
    
        temp_rect = Rect_new(current_window->y, current_window->x,
                             current_window->y + current_window->height - 1,
                             current_window->x + current_window->width - 1);
        Context_add_clip_rect(desktop->context, temp_rect);
    }

    //Draw the clipping rects
    for(i = 0; i < desktop->context->clip_rects->count; i++) {

        temp_rect = (Rect*)List_get_at(desktop->context->clip_rects, i);
        Context_draw_rect(desktop->context, temp_rect->left, temp_rect->top,
                          temp_rect->right - temp_rect->left + 1,
                          temp_rect->bottom - temp_rect->top + 1,
                          0xFF00FF00);
    }

    //For now, we'll just draw a simple rectangle for the mouse (since that's
    //our only drawing primitive)
    Context_fillRect(desktop->context, desktop->mouse_x, desktop->mouse_y, 10, 10, 0xFFFF0000);
}

//================| Rect Class Implementation |================//

//Allocate a new rectangle object
Rect* Rect_new(int top, int left, int bottom, int right) {

    //Attempt to allocate the object
    Rect* rect;
    if(!(rect = (Rect*)page_allocator(sizeof(Rect))))
        return rect;

    //Assign intial values
    rect->top = top;
    rect->left = left;
    rect->bottom = bottom;
    rect->right = right;

    return rect;
}

//Explode subject_rect into a list of contiguous rects which are
//not occluded by cutting_rect
// ________                ____ ___
//|s    ___|____          |o   |o__|
//|____|___|   c|   --->  |____|          
//     |________|              
List* Rect_split(Rect* subject_rect, Rect* cutting_rect) {

    //Allocate the list of result rectangles
    List* output_rects;
    if(!(output_rects = List_new()))
        return output_rects;

    //We're going to modify the subject rect as we go,
    //so we'll clone it so as to not upset the object 
    //we were passed
    Rect subject_copy;
    subject_copy.top = subject_rect->top;
    subject_copy.left = subject_rect->left;
    subject_copy.bottom = subject_rect->bottom;
    subject_copy.right = subject_rect->right;

    //We need a rectangle to hold new rectangles before
    //they get pushed into the output list
    Rect* temp_rect;

    //Begin splitting
    //1 -Split by left edge if that edge is between the subject's left and right edges 
    if(cutting_rect->left > subject_copy.left && cutting_rect->left <= subject_copy.right) {

        //Try to make a new rectangle spanning from the subject rectangle's left and stopping before 
        //the cutting rectangle's left
        if(!(temp_rect = Rect_new(subject_copy.top, subject_copy.left,
                                  subject_copy.bottom, cutting_rect->left - 1))) {

            //If the object creation failed, we need to delete the list and exit failed
            // free(output_rects);

            return (List*)0;
        }

        //Add the new rectangle to the output list
        List_add(output_rects, temp_rect);

        //Shrink the subject rectangle to exclude the split portion
        subject_copy.left = cutting_rect->left;
    }

    //2 -Split by top edge if that edge is between the subject's top and bottom edges 
    if(cutting_rect->top > subject_copy.top && cutting_rect->top <= subject_copy.bottom) {

        //Try to make a new rectangle spanning from the subject rectangle's top and stopping before 
        //the cutting rectangle's top
        if(!(temp_rect = Rect_new(subject_copy.top, subject_copy.left,
                                  cutting_rect->top - 1, subject_copy.right))) {

            //If the object creation failed, we need to delete the list and exit failed
            //This time, also delete any previously allocated rectangles
            while(output_rects->count) {
                
                temp_rect = List_remove_at(output_rects, 0);
                // free(temp_rect);
            }

            // free(output_rects);

            return (List*)0;
        }

        //Add the new rectangle to the output list
        List_add(output_rects, temp_rect);

        //Shrink the subject rectangle to exclude the split portion
        subject_copy.top = cutting_rect->top;
    }

    //3 -Split by right edge if that edge is between the subject's left and right edges 
    if(cutting_rect->right >= subject_copy.left && cutting_rect->right < subject_copy.right) {

        //Try to make a new rectangle spanning from the subject rectangle's right and stopping before 
        //the cutting rectangle's right
        if(!(temp_rect = Rect_new(subject_copy.top, cutting_rect->right + 1,
                                  subject_copy.bottom, subject_copy.right))) {

            //Free on fail
            while(output_rects->count) {
                
                temp_rect = List_remove_at(output_rects, 0);
                // free(temp_rect);
            }

            // free(output_rects);

            return (List*)0;
        }

        //Add the new rectangle to the output list
        List_add(output_rects, temp_rect);

        //Shrink the subject rectangle to exclude the split portion
        subject_copy.right = cutting_rect->right;
    }

    //4 -Split by bottom edge if that edge is between the subject's top and bottom edges 
    if(cutting_rect->bottom >= subject_copy.top && cutting_rect->bottom < subject_copy.bottom) {

        //Try to make a new rectangle spanning from the subject rectangle's bottom and stopping before 
        //the cutting rectangle's bottom
        if(!(temp_rect = Rect_new(cutting_rect->bottom + 1, subject_copy.left,
                                  subject_copy.bottom, subject_copy.right))) {

            //Free on fail
            while(output_rects->count) {
                
                temp_rect = List_remove_at(output_rects, 0);
                // free(temp_rect);
            }

            // free(output_rects);

            return (List*)0;
        }

        //Add the new rectangle to the output list
        List_add(output_rects, temp_rect);

        //Shrink the subject rectangle to exclude the split portion
        subject_copy.bottom = cutting_rect->bottom;
    }
 
    //Finally, after all that, we can return the output rectangles 
    return output_rects;
}

//================| Context Class Implementation |================//

//Constructor for our context
Context* Context_new(uint16_t width, uint16_t height, uint32_t* buffer) {

    //Attempt to allocate
    Context* context;
    if(!(context = (Context*)page_allocator(sizeof(Context))))
        return context; 

    //Attempt to allocate new rect list 
    if(!(context->clip_rects = List_new())) {

        // free(context);
        return (Context*)0;
    }

    //Finish assignments
    context->width = width; 
    context->height = height; 
    context->buffer = buffer;

    return context;
}

//A horizontal line as a filled rect of height 1
void Context_horizontal_line(Context* context, int x, int y,
                             unsigned int length, uint32_t color) {

    Context_fillRect(context, x, y, length, 1, color);
}

//A vertical line as a filled rect of width 1
void Context_vertical_line(Context* context, int x, int y,
                           unsigned int length, uint32_t color) {

    Context_fillRect(context, x, y, 1, length, color);
}

//Rectangle drawing using our horizontal and vertical lines
void Context_draw_rect(Context* context, int x, int y, 
                       unsigned int width, unsigned int height, uint32_t color) {

    Context_horizontal_line(context, x, y, width, color); //top
    Context_vertical_line(context, x, y + 1, height - 2, color); //left 
    Context_horizontal_line(context, x, y + height - 1, width, color); //bottom
    Context_vertical_line(context, x + width - 1, y + 1, height - 2, color); //right
}

//Insert the passed rectangle into the clip list, splitting all
//existing clip rectangles against it to prevent overlap
void Context_add_clip_rect(Context* context, Rect* added_rect) {

    //Check each item already in the list to see if it overlaps with
    //the new rectangle
    int i, j;
    Rect* cur_rect;
    List* split_rects;

    for(i = 0; i < context->clip_rects->count; ) {

        cur_rect = List_get_at(context->clip_rects, i);

        //Standard rect intersect test (if no intersect, skip to next)
        //see here for an example of why this works:
        //http://stackoverflow.com/questions/306316/determine-if-two-rectangles-overlap-each-other#tab-top
        if(!(cur_rect->left <= added_rect->right &&
		   cur_rect->right >= added_rect->left &&
		   cur_rect->top <= added_rect->bottom &&
		   cur_rect->bottom >= added_rect->top)) {

            i++;
            continue;
        }

        //If this rectangle does intersect with the new rectangle, 
        //we need to split it
        List_remove_at(context->clip_rects, i); //Original will be replaced w/splits
        split_rects = Rect_split(cur_rect, added_rect); //Do the split
        // free(cur_rect); //We can throw this away now, we're done with it

        //Copy the split, non-overlapping result rectangles into the list 
        while(split_rects->count) {

            cur_rect = (Rect*)List_remove_at(split_rects, 0);
            List_add(context->clip_rects, cur_rect);
        }

        //Free the empty split_rect list 
        // free(split_rects);

        //Since we removed an item from the list, we need to start counting over again 
        //In this way, we'll only exit this loop once nothing in the list overlaps 
        i = 0;    
    }

    //Now that we have made sure none of the existing rectangles overlap
    //with the new rectangle, we can finally insert it 
    List_add(context->clip_rects, added_rect);
}

//Remove all of the clipping rects from the passed context object
void Context_clear_clip_rects(Context* context) {

    Rect* cur_rect;

    //Remove and free until the list is empty
    while(context->clip_rects->count) {

        cur_rect = (Rect*)List_remove_at(context->clip_rects, 0);
        // free(cur_rect);
    }
}