//
// Created by Michael Fields on 3/7/21.
//

#include "State.h"

#ifndef QSM_LIGHTONSTATE_H
#define QSM_LIGHTONSTATE_H


class LightOnState : public State {
public:
    LightOnState() : LightOnState(nullptr) { };
    LightOnState(StateMachine * sm);
    virtual State* ProcessEvent(Event event);
    virtual State* Enter();
    virtual void Exit();
};


#endif //QSM_LIGHTONSTATE_H
