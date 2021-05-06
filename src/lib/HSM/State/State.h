

#ifndef HSMState_
#define HSMState_

#include "../StateMachine/StateMachine.h"
#include <iostream>
class StateMachine;

class State {
public:
    State();


    // One for each edge
    //---
    virtual void TIMEOUT() {
        std::cout << "TIMEOUT Unhandled. Logging.." << std::endl;
    };
    //---


    virtual void Entry() = 0;
    virtual void Exit() = 0;

    StateMachine* _context = nullptr;

    //Used for exit/enter call stack
    State* _parent = nullptr;
    int level = -1;


protected:
    void ChangeState(StateMachine*, State*);
    void InitialTransition(StateMachine*, State*);
};

#endif