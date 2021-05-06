#ifndef HSMState_
#define HSMState_

#include "../HSM/HSM.h"
#include <iostream>
#include <thread>
class HSM;

class HSMState {
public: 
    HSMState();

    virtual void TIMEOUT() {
        std::cout << "TIMEOUT Unhandled. Logging.." << std::endl;
    }
    virtual void JUNCTION_EVENT() {
        std::cout << "JUNCTION_EVENT Unhandled. Logging.." << std::endl;
    }
    virtual void LOOP_EVENT() {
        std::cout << "LOOP_EVENT Unhandled. Logging.." << std::endl;
    }
    virtual void ARM_ROCKETS() {
        std::cout << "ARM_ROCKETS Unhandled. Logging.." << std::endl;
    }

    std::string stateName;

    virtual void Entry() = 0;
    virtual void Exit() = 0;

    HSM* _context;

    //Used for exit/enter call stack
    HSMState* _parent;
    int level = -1;

protected:
    void ChangeState(HSM*, HSMState*);
};

#endif

