#include "Calc.h"
#include <iostream>

Calc::Calc()
{
}

Calc::~Calc()
{
}

int Calc::min(int a, int b)
{
	return a < b ? a : b;
}

int Calc::max(int a, int b)
{
	return a > b ? a : b;
}