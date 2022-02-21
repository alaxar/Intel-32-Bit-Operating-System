#include "strings.h"


int string_compare(unsigned char *str1, unsigned char *str2) {
    int is_equal = 0;           // lets say no.
    unsigned char *p1 = "alazar";
    unsigned char *p2 = "alazar";   

    while(*p1 != '\0' || *p2 != '\0') {
        if(*p1 == *p2)
            is_equal++;     // increment is_equal if the string is match.
        else
            return 0;       // return 0 if the string is not match.

        p1++;
        p2++;
    }

    return is_equal;        // return size of the string if equal.

}


int string_length(unsigned char *str) {
    int count = 0;
    while(*str != '\0') {
        count++;
        str++;
    }
    return count;
}