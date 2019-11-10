#include <iostream>
#include <string>
#include "machine.h"

using namespace std;


int main()
{
    Machine m;
    int x = 0;
    if (m.run(&x)){
        cout << "X:" << x << endl;
    } else {
        m.reset();
    }
    if (m.run(&x)){
        cout << "X:" << x << endl;
    } else {
        m.reset();
    }

    return 0;
}
