#ifndef TRACER_H
#define TRACER_H

#include <stddef.h>

class _Tracer
{
private:
	static int x;
	int num;
	void printTrace(const char * funcName);
	
public:
	_Tracer();
	_Tracer(const _Tracer&);
	~_Tracer();
	_Tracer& operator=(const _Tracer&);
	/*static*/ void * operator new(size_t s);
	/*static*/ void operator delete(void * p);
	static void setX(int value);
	static int getX();
};

class Tracer: public _Tracer
{
};

#endif//TRACER_H