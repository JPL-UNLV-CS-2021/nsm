/**
 The State class is intended to be a base class for leaf states
**/

#include <iostream>
#include <map>
#include <vector>

#ifndef QSM_STATE_H
#define QSM_STATE_H

using namespace std;

class StateMachine;
class Event;

class State {

public:
    State(StateMachine* sm);
    virtual State* ProcessEvent(Event event);
    virtual State* Enter() = 0;
    virtual void Exit() = 0;
    void AddTransition(string eventName, State * nextState);
    string GetStateName();

protected:
    void PrintEnter();
    void PrintExit();

    void SetTimeOut(int seconds);
    void CancelTimeout();

    StateMachine* _stateMachine;
    State * _last;


    map<string, State *> _eventHandlers;
    string _stateName;

    vector<State*> _subStates;
    State* _lastVisited;

private:
    void TimerFunction(int seconds);
    atomic_bool _timeoutRunning;
    thread* _timerThread;

};

#endif //QSM_STATE_H
