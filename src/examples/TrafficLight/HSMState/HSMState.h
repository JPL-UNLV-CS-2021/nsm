#ifndef HSMState_
#define HSMState_

#include "../HSM/HSM.h"
#include <iostream>
#include <thread>
class HSM;

class HSMState {
public:
    HSMState();

    virtual void OFF() {
        std::cout << "OFF Unhandled. Logging.." << std::endl;
    }
    virtual void TIMEOUT() {
        std::cout << "TIMEOUT Unhandled. Logging.." << std::endl;
    }
    virtual void PEDESTRIAN_WAITING() {
        std::cout << "PEDESTRAIN_WAITING Unhandled. Logging.." << std::endl;
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
    void InitialTransition(HSM*, HSMState*);
};

#endif