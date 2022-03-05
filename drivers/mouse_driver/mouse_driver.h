#ifndef _MOUSE_H_
#define _MOUSE_H_

void mouse_handler();
void mouse_install();
void mouse_write(unsigned char a_write);
unsigned char mouse_read();
void mouse_wait(unsigned char a_type);


#endif