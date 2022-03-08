#ifndef _EVENT_HANDLER_H_
#define _EVENT_HANDLER_H_

#include "../../advanced_array.h"

void addEvent(int window_id, void (*callback)());
void eventCaller();
EthiopicArray *CheckRegisteredBtn();
#endif