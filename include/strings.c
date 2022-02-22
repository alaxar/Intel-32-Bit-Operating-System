#include "strings.h"


int string_compare(unsigned char *str1, unsigned char *str2, int size) {
    int is_equal = 0, i = 0;                   // lets say no.
    unsigned char *p1 = (unsigned char*)str1;
    unsigned char *p2 = (unsigned char*)str2;   

    while(i < size) {           // for security reasons we need the size from the user.
        if(*p1 == *p2)
            is_equal++;     // increment is_equal if the string is match.
        else
            return 0;       // return 0 if the string is not match.

        p1++;
        p2++;
        i++;
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