#include "event_handler.h"

void (*func)(void);
EthiopicArray *buttons;

int isRegistered = 0;

void addEvent(int window_id, void (*callback)()) {
    if(search(window_id) <= 0) {
        DrawText(0, 0, "NOT REGISTERED");
        insert(window_id, callback);
    }
    else
    {
        DrawText(0, 0, "REGISTERED");
    }
}