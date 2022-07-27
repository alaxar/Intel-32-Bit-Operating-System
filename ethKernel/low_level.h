#ifndef _LOW_LEVEL
#define _LOW_LEVEL
unsigned char port_byte_in(unsigned short port);
void port_byte_out(unsigned short port, unsigned char data);
unsigned short port_word_in(unsigned short port);
void port_word_out(unsigned short port, unsigned short data);

void port_dword_out(unsigned short port, unsigned long data);
unsigned long port_dword_in(unsigned short port);

#endif