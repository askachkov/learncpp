#ifndef MACHINE_H
#define MACHINE_H

class Machine
{
public:
    enum State
    {
        State_1,
        State_2,
        State_3,
        State_Error,
        State_End,
    };

private:
    typedef State (Machine::*Stage)();

private:
    State fctState_1();
    State fctState_2();
    State fctState_3();
    State fctError();

private:
    State m_currentStage;

private:
    static const Stage STAGE[4];

public:
    Machine();
    bool run(int * out);
    void reset();
    State state()const;
};


#endif // MACHINE_H
