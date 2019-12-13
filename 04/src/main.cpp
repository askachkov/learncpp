#include <iostream>
#include "Calc.h"

#ifdef BUILD_TESTS
#include <UnitTest++/UnitTest++.h>
#endif//BUILD_TESTS

using namespace std;

int main(int argc, char * argv[])
{
	Calc calc;
	cout << "Hello World!" << endl;
#ifdef BUILD_TESTS
	UnitTest::RunAllTests();
#endif//BUILD_TESTS
	return 0;
}
