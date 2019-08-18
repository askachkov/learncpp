#include <stdio.h>
#include <stdlib.h>
#include "tracer.h"

class Record
{
	Tracer one;
	Tracer two;
};

int main(int argc, char * argv[])
{
	Tracer * pB;
	{
		Tracer a;
		pB = new Tracer(a);
	}
	delete pB;
	
	{
		Record r1;
		Record * pr2 = new Record(r1);
		delete pr2;
	}
	
	getchar();
	return 0;
}