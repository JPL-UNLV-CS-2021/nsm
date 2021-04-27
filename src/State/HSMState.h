

#ifndef HSMState_
#define HSMState_

#include "../HSM/HSM.h"
#include <iostream>
class HSM;

class HSMState {
public:
    HSMState();


    // One for each edge
    //---
    virtual void TIMEOUT() {
        std::cout << "TIMEOUT Unhandled. Logging.." << std::endl;
    };
    //---


    virtual void Entry() = 0;
    virtual void Exit() = 0;

    HSM* _context = nullptr;

    //Used for exit/enter call stack
    HSMState* _parent = nullptr;
    int level = -1;


protected:
    void ChangeState(HSM*, HSMState*);
    void InitialTransition(HSM*, HSMState*);
};

#endif