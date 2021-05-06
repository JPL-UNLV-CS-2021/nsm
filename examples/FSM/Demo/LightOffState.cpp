//
// Created by Michael Fields on 3/7/21.
//

#include <iostream>
#include "LightOffState.h"
#include "StateMachine.h"
#include "Event.h"

using namespace std;

LightOffState::LightOffState(StateMachine *sm) : State(sm) {
    this->_stateName = "light off";
}

State * LightOffState::ProcessEvent(Event event) {
    cout << "process event from light off - " << event.Name << endl;
    return State::ProcessEvent(event);
}


State* LightOffState::Enter() {
    PrintEnter();
    return this;
}

void LightOffState::Exit() {
    PrintExit();
}
