#ifndef _ADVANCED_ARRAY_H_
#define _ADVANCED_ARRAY_H_

#include "types.h"

typedef struct advanced_array
{
    int key;
    char *value;
    struct advanced_array *next;
};

void insert(int key, int value);
int search(int key);

#endif