#include "Calc.h"
#include <iostream>

static void printMsg(const char * str)
{
	using namespace std;
	cout << "Msg: " << str << endl;
}

Calc::Calc()
{
	printMsg("Calc Ctor");	
}

Calc::~Calc()
{
	printMsg("Calc Dtor");
}