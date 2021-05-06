//
// Created by Michael Fields on 3/7/21.
//

#include <iostream>
#include "LightOnState.h"
#include "Event.h"
#include "StateMachine.h"

using namespace std;


LightOnState::LightOnState(StateMachine* sm) : State(sm) {
    this->_stateName = "light on";
}

State * LightOnState::ProcessEvent(Event event) {
    cout << "process event from light on - " << event.Name << endl;
    return State::ProcessEvent(event);
}

State* LightOnState::Enter() {
    PrintEnter();
    State::SetTimeOut(5);
    return this;
}

void LightOnState::Exit() {
  State::CancelTimeout();
  PrintExit();
}