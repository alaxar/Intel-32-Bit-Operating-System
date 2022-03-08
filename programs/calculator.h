#ifndef CALCULATOR_H_
#define CALCULATOR_H_

// file inclusion
#include "../include/gui/gui.h"

// varible declaration
int a, b;
int result;


// window creation
// function declaration
void InitCalculator();
void Calculate();
void exit();

int sum(int x, int y);
int sub(int x, int y);
int mul(int x, int y);


#endif