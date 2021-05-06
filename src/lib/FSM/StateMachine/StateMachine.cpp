/**
// The StateMachine class is a concrete class for a state machine object.
// It is akin to the Context class in the GOF design pattern on State.  
**/

#include "StateMachine.h"
#include <time.h>
#include <thread>

StateMachine::StateMachine() {
    InitializeState();
    InitializeEventQueue();
}

void StateMachine::InitializeState() {

    /** TODO: add state initialization code
     * Sample code for state initialization
     * State* INIT_STATE  = new LightOffState(this);
     * State* NEXT_STATE =  new LightOnState(this);
     * INIT_STATE->AddTransition("switch-on", NEXT_STATE);
     * NEXT_STATE->AddTransition("switch-off", INIT_STATE);
     * NEXT_STATE->AddTransition("timeout", INIT_STATE);
     * this->_currentState = INIT_STATE;
     **/
}

void StateMachine::InitializeEventQueue() {
    /** TODO: add event queue initialize code
     * Sample code for event queue initialization
     * this->_eventQueue.push(Event("switch-on", "external"));
     * this->_eventQueue.push(Event("switch-off", "external", 500));
     * this->_eventQueue.push(Event("switch-on", "external", 500));
     **/
}


void StateMachine::Run() {

    cout << "Starting State Machine" << endl;

    clock_t t;
    t = clock();

    while(!_eventQueue.empty()) {

        Event event = _eventQueue.front();

        if(clock() - t > event.Timing)
        {
            dispatch(event);
            t = clock();
            _eventQueue.pop();
        } else {
            cout << "waiting for events..." << endl;
            this_thread::sleep_for(chrono::seconds(1));
        }
    }
}

// Update Current State
void StateMachine::updateCurrentState(State* s) {

    this->_currentState->Exit();
    cout << "Transitioning to " << s->GetStateName() << endl;
    s->Enter();

    this->_currentState = s;
}

// Getter for _currentState pointer
State* StateMachine::currentState() {
    return this->_currentState;
}

// Main dispatch method
// As per GOF State Design pattern (ProcessEvent() <=> Handle())
State* StateMachine::dispatch(Event e) {

    State* nextState = this->currentState()->ProcessEvent(e);
    // If not null pointer
    if(nextState) {
        this->updateCurrentState(nextState);
    }

    return  nextState;
}
