
#ifndef HSM_
#define HSM_
#include "../State/State.h"
#include <iostream>
#define H_LEVEL 1

class State;

class StateMachine {
public:
    HSM();
    void START();
    void initalizeMemory();
    //A list of all events in the system

    void TIMEOUT();

    //Global Vars
    //NONE

    //State Design
    State* _state;
    friend class State;
    void ChangeState(State*);
    void InitialTransition(State*);
    void HandleEntryExit(State*, State*);
    //CallStacks
    //The length of these arrays is equal to
    //the height of the heirarchial state machine
    State* entryStates[H_LEVEL];
    State* exitStates[H_LEVEL];
    int numOfEntryStates;
    int numOfExitStates;
    State* commonParent;


};

#endif 
