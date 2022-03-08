#ifndef _ADVANCED_ARRAY_H_
#define _ADVANCED_ARRAY_H_

#include "types.h"

typedef struct advanced_array
{
    int key;
    int value;
    void *addressValue;
    struct advanced_array *next;
} EthiopicArray;

void insert(int key, void* value);
void *search(int key);

#endif