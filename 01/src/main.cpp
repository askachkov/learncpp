#include <stdio.h>
#include <stdlib.h>
#include <utility>
#include <new>

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
		_Tracer(const _Tracer&&)
		{
			num = x++;
			printTrace("MoveCtor");
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
		_Tracer& operator=(const _Tracer&&)
		{
			printTrace("MoveEqual");
			return *this;
		}
		
		//https://en.cppreference.com/w/cpp/memory/new/operator_new
		//https://en.cppreference.com/w/cpp/memory/new/operator_delete
		
		/*static*/ void * operator new(size_t s)
		{
			printf("Tracer: new %d\n", s);
			return calloc(s, 1);
		}
		/*static*/ void operator delete(void * p)
		{
			printf("Tracer: delete\n");
			free(p);
		}
		
		/*static*/ void * operator new[](size_t s)
		{
			printf("Tracer: new[] %d\n", s);
			return calloc(s, 1);
		}
		/*static*/ void operator delete[](void * p)
		{
			printf("Tracer: delete[]\n");
			free(p);
		}
		
		/*static*/ void * operator new(size_t s, void *p)
		{
			printf("Tracer: placement new\n");
			return p;
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
		Tracer * mem = (Tracer*)malloc(sizeof(Tracer));
		
		Tracer a;
		new (mem) Tracer;
		pB = mem;
		
		Tracer c = std::move(a);
		Tracer d;
		d = std::move(c);
	}
	printf("Tracer: remove object from 'placement new'\n");
	pB->~Tracer();
	free(pB);
	
	pB = new Tracer;
	delete pB;
	
	pB = new Tracer[4];
	delete[] pB;
	
	
	{
		Record r1;
		Record * pr2 = new Record(r1);
		delete pr2;
	}
	
	getchar();
	return 0;
}