#include "machine.h"
#include <iostream>

using namespace std;

const Machine::Stage Machine::STAGE[4] = {&Machine::fctState_1, &Machine::fctState_2, &Machine::fctState_3, &Machine::fctError};

Machine::Machine():
    m_currentStage(State_1)
{

}

Machine::State Machine::fctState_1()
{
    cout << "State_1" << endl;
    return State_2;
}

Machine::State Machine::fctState_2()
{
    cout << "State_2" << endl;
    return State_3;
}

Machine::State Machine::fctState_3()
{
    static int x = 0;
    cout << "State_3" << endl;
    if ( !x ){
        x++;
        return State_Error;
    }
    return State_End;
}

Machine::State Machine::fctError()
{
    cout << "fctError" << endl;
    return State_Error;
}

bool Machine::run(int *out)
{
    do {
        m_currentStage = (this->*STAGE[m_currentStage])();
        if ( m_currentStage == State_Error )
            return false;
        if ( m_currentStage == State_End ){
            *out = 7;
            return true;
        }
    } while ( true );
}

void Machine::reset()
{
    cout << "Reset" << endl;
    m_currentStage = State_1;
}

Machine::State Machine::state() const
{
    return m_currentStage;
}
