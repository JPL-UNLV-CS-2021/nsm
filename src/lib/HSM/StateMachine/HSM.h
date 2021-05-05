
#ifndef HSM_
#define HSM_
#include "../HSMState/HSMState.h"
#include <iostream>
#define H_LEVEL 1

class HSMState;

class HSM {
public:
    HSM();
    void START();
    void initalizeMemory();
    //A list of all events in the system

    void TIMEOUT();

    //Global Vars
    //NONE

    //State Design
    HSMState* _state;
    friend class HSMState;
    void ChangeState(HSMState*);
    void InitialTransition(HSMState*);
    void HandleEntryExit(HSMState*, HSMState*);
    //CallStacks
    //The length of these arrays is equal to
    //the height of the heirarchial state machine
    HSMState* entryStates[H_LEVEL];
    HSMState* exitStates[H_LEVEL];
    int numOfEntryStates;
    int numOfExitStates;
    HSMState* commonParent;


};

#endif 
