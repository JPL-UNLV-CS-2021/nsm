//
// Author: Daniel Hartwig
// Originally created: 2021-02-26
//
// The StateMachine class is a concrete class for a state machine object.
// It is akin to the Context class in the GOF design pattern on State.  
//



#include <string>
#include <queue>
#include "../Events/Event.h"

#ifndef QSM_STATEMACHINE_H
#define QSM_STATEMACHINE_H


using namespace std;

//class Event;
class State;

class StateMachine {
    public:
        // Constructor
        StateMachine();
        
        void Run();
        void InitializeState();
        void InitializeEventQueue();

        State* dispatch(Event e);
        // Get current state
        State* currentState();

        // Update current state
        void updateCurrentState(State* s);

    private:
        // Pointer to current state
        State* _currentState;
        queue<Event> _eventQueue;
};



#endif
