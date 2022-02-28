#include "math.h"

uint32_t absolute(int value) {
    if(value < 0)
        return (value * -1);
    
    return value;
}