#include "event_handler.h"

void (*func)(void);

void addEvent(int window_id, void (*callback)()) {
    // register callback function for window_id
    func = callback;    
}

void eventCaller(){
    func();
}