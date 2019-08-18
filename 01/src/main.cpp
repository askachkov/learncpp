#include <stdio.h>
#include <stdlib.h>

int x = 0;

class _Tracer
{
		int num;
		void printTrace(const char * funcName)
		{
			printf("Tracer %d: %s\n", num, funcName);
		}
		
	public:
		_Tracer()
		{
			num = x++;
			printTrace("Ctor");
		}
		_Tracer(const _Tracer&)
		{
			num = x++;
			printTrace("CopyCtor");
		}
		~_Tracer()
		{
			printTrace("Dtor");
		}
		_Tracer& operator=(const _Tracer&)
		{
			printTrace("OpEqual");
			return *this;
		}
		/*static*/ void * operator new(size_t s)
		{
			printf("Tracer: new\n");
			return calloc(s, 1);
		}
		/*static*/ void operator delete(void * p)
		{
			printf("Tracer: delete\n");
			free(p);
		}
};

class Tracer: public _Tracer
{
};

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