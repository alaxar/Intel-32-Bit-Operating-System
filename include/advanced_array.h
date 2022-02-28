#ifndef _ADVANCED_ARRAY_H_
#define _ADVANCED_ARRAY_H_

typedef struct advanced_array
{
    int key;
    char *value;
    struct advanced_array *next;
};

void insert(int key, int value);


#endif