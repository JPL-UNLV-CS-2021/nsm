//#include all states

#include "StateMachine.h"


StateMachine::StateMachine() {
    //INIT ALL STATES
    initalizeMemory();
}

void StateMachine::initalizeMemory() {

    // Example Initialization of Generated State Classes as Singletons

    // // Example state "Off"
    // static Off a;
    // a._self = &a;
    // a._context = this;
    // a.level = 0;
    // a._parent = NULL;

    // // Example state "On"
    // static On b;
    // b._self = &b;
    // b._context = this;
    // b.level = 0;
    // b._parent = NULL;

}


void StateMachine::ChangeState(State* s) {

    //This function fills entry and exit array
    HandleEntryExit(_state, s);

    for (int i = 0; i < numOfExitStates; i++) {
        exitStates[i]->Exit();
    }

    //while (_state->level >= commonParent->level) {
    //    _state->Exit();
    //    if (_state->_parent == NULL) {
    //        break;
    //    }
    //    _state = _state->_parent;
    //}
    //_state->Exit();
    _state = s;

    for (int i = numOfEntryStates - 1; i >= 0; i--) {
        entryStates[i]->Entry();
    }

    //_state->Entry();
}

void StateMachine::InitialTransition(State* s) {
    _state = s;
    _state->Entry();
}


void StateMachine::HandleEntryExit(State* FROM, State* TO) {
    State* fromOriginal = FROM;
    State* toOriginal = TO;
    numOfEntryStates = 0;
    numOfExitStates = 0;
    //Check current Levels
    while (FROM->level != TO->level) {
        if (FROM->level > TO->level) {

            exitStates[numOfExitStates] = FROM;
            numOfExitStates++;
            FROM = FROM->_parent;
        }
        else {

            entryStates[numOfEntryStates] = TO;
            numOfEntryStates++;
            TO = TO->_parent;
        }
    }

    // At this point both states are on same level
    //     0
    //    /|\
    //   0 0 0 <-

    while (FROM != TO) {

        exitStates[numOfExitStates] = FROM;
        numOfExitStates++;
        FROM = FROM->_parent;

        entryStates[numOfEntryStates] = TO;
        numOfEntryStates++;
        TO = TO->_parent;
    }

    commonParent = TO; //Could use either TO or FROM

    FROM = fromOriginal;
    TO = toOriginal;
}

//This handles the first state the system enters
void StateMachine::START() {
    // Example: Set initial state
    // this->_state = Off::Instance();
    _state->Entry();

}

void StateMachine::TIMEOUT() {
    _state->TIMEOUT();
}