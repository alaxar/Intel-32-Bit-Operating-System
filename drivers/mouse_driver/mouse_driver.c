
//License: Use as you wish, except to cause damage
unsigned char mouse_cycle=0;     //unsigned char
char mouse_byte[3];    //signed char
int mouse_x = 1;         //signed char
int mouse_y = 1;         //signed char

//Mouse functions
void mouse_handler() 
{

      mouse_byte[0]=port_byte_in(0x60);
      mouse_cycle++;
      mouse_byte[1]=port_byte_in(0x60);
      mouse_cycle++;
      mouse_byte[2]=port_byte_in(0x60);
      mouse_x +=mouse_byte[1];
      mouse_y -=mouse_byte[2];
      mouse_cycle=0;
}

void mouse_wait(unsigned char a_type) //unsigned char
{
  unsigned int _time_out=100000; //unsigned int
  if(a_type==0)
  {
    while(_time_out--) //Data
    {
      if((port_byte_in(0x64) & 1)==1)
      {
        return;
      }
    }
    return;
  }
  else
  {
    while(_time_out--) //Signal
    {
      if((port_byte_in(0x64) & 2)==0)
      {
        return;
      }
    }
    return;
  }
}

void mouse_write(unsigned char a_write) //unsigned char
{
  //Wait to be able to send a command
  mouse_wait(1);
  //Tell the mouse we are sending a command
  port_byte_out(0x64, 0xD4);
  //Wait for the final part
  mouse_wait(1);
  //Finally write
  port_byte_out(0x60, a_write);
}

unsigned char mouse_read()
{
  //Get's response from mouse
  mouse_wait(0);
  return port_byte_in(0x60);
}

void mouse_install()
{
  unsigned char _status;  //unsigned char

  //Enable the auxiliary mouse device
  mouse_wait(1);
  port_byte_out(0x64, 0xA8);
 
  //Enable the interrupts
  mouse_wait(1);
  port_byte_out(0x64, 0x20);
  mouse_wait(0);
  _status=(port_byte_in(0x60) | 2);
  mouse_wait(1);
  port_byte_out(0x64, 0x60);
  mouse_wait(1);
  port_byte_out(0x60, _status);
 
  //Tell the mouse to use default settings
  mouse_write(0xF6);
  mouse_read();  //Acknowledge
 
  //Enable the mouse
  mouse_write(0xF4);
  mouse_read();  //Acknowledge

  //Setup the mouse handler
  irq_install_handler(12, mouse_handler);
}