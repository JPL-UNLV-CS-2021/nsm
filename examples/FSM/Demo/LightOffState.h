//
// Created by Michael Fields on 3/7/21.
//

#include "State.h"


#ifndef QSM_LIGHTOFFSATE_H
#define QSM_LIGHTOFFSATE_H

class LightOffState : public State {
public:
    LightOffState() : LightOffState(nullptr) { };
    LightOffState(StateMachine* sm);
    virtual State* ProcessEvent(Event event);
    virtual State* Enter();
    virtual void Exit();
};


#endif //QSM_LIGHTOFFSATE_H
