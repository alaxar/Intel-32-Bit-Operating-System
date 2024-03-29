#include "low_level.h"

unsigned char port_byte_in(unsigned short port) {
    unsigned char result;
    __asm__("in %%dx, %%al" : "=a"(result) : "d"(port));
    return result;
}

void port_byte_out(unsigned short port, unsigned char data) {
    __asm__("out %%al, %%dx" : : "a"(data), "d"(port));
}

unsigned short port_word_in(unsigned short port) {
    unsigned short result;
    __asm__("in %%dx, %%al" : "=a"(result) : "d"(port));
    return result;
}

void port_word_out(unsigned short port, unsigned short data) {
    __asm__("out %%al, %%dx" : : "a"(data), "d"(port));
}

void port_dword_out(unsigned short port, unsigned long data) {
    __asm__("out %%eax, %%dx" : : "a"(data), "d"(port));
}

unsigned long port_dword_in(unsigned short port) {
    unsigned long result;
    __asm__("in %%dx, %%eax" : "=a"(result) : "d"(port));
    return result;
}