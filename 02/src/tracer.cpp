#include "tracer.h"
#include <stdio.h>
#include <stdlib.h>

int _Tracer::x = 0;

void _Tracer::printTrace(const char * funcName)
{
	printf("Tracer %d: %s\n", num, funcName);
}

_Tracer::_Tracer()
{
	num = x++;
	printTrace("Ctor");
}

_Tracer::_Tracer(const _Tracer&)
{
	num = x++;
	printTrace("CopyCtor");
}

_Tracer::~_Tracer()
{
	printTrace("Dtor");
}

_Tracer& _Tracer::operator=(const _Tracer&)
{
	printTrace("OpEqual");
	return *this;
}

void * _Tracer::operator new(size_t s)
{
	printf("Tracer: new\n");
	return calloc(s, 1);
}

void _Tracer::operator delete(void * p)
{
	printf("Tracer: delete\n");
	free(p);
}

void _Tracer::setX(int value)
{
	x = value;
}

int _Tracer::getX()
{
	return x;
}
