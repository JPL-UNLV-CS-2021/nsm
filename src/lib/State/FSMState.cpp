//
// Created by Michael Fields on 2/23/21.
//

#include <iostream>
#include <thread>
#include <chrono>
#include <string>
#include "FSMState.h"
#include "../StateMachine/FSMStateMachine.h"
#include "../Events/Event.h"

using namespace std;

State::State(StateMachine *sm) {
    this->_stateMachine = sm;
}

State* State::Enter() {
    cout << "Entering State" << endl;
    return this;
}

void State::Exit() {
    cout << "Exiting State" << endl;
}

void State::CancelTimeout() {

    if(this->_timeoutRunning) {
        cout << "Cancelling Timeout" << endl;
        this->_timeoutRunning = false;
        this->_timerThread->join();
        delete this->_timerThread;
        this->_timerThread = NULL;
    }
}

State* State::ProcessEvent(Event event) {

    auto nextState = _eventHandlers.find(event.Name);
    if(nextState != _eventHandlers.end()) {
        return _eventHandlers[event.Name];
    };

    return NULL;
}

string State::GetStateName() {
    return _stateName;
}

void State::AddTransition(string eventName, State *nextState) {
    cout << "adding transition from " << _stateName
        << " for " << eventName << " to " << nextState->GetStateName() << endl;
    _eventHandlers[eventName] = nextState;
}


void State::PrintEnter() {
    cout << "entering " << _stateName << endl;
}

void State::PrintExit() {
    cout << "exiting " << _stateName << endl;
}

State* State::ProcessChildren(Event event) {

    /*if(_subStates.empty()) {
        for (auto child = _subStates.begin(); child != _subStates.end(); ++child) {
            auto result = child->ProcessEvent(event);
            if(result != NULL) {
                return result;
            }
        }
//    }*/

    return NULL;
}


void State::SetTimeOut(int seconds) {

    if(seconds < 1) {
        return;
    }
    _timerThread = new thread(&State::TimerFunction, this, seconds);
}

void State::TimerFunction(int seconds) {

    int count = 0;
    this->_timeoutRunning = true;


    while(this->_timeoutRunning) {

        this_thread::sleep_for(chrono::seconds(1));
        if(++count >= seconds) {
            this->_timeoutRunning = false;
            this->_stateMachine->dispatch(Event("timeout", "internal"));
            break;
        }
    }
}

