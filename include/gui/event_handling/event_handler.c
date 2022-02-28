#include "event_handler.h"


void addEvent(int window_id, void (*callback)()) {
    // register callback function for window_id
    callback();
}