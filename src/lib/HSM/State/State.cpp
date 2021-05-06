#include "State.h"

HSMState::State() {
}

void State::ChangeState(StateMachine* t, State* s) {
    t->ChangeState(s);
}

void State::InitialTransition(StateMachine* t, State* s) {
    t->InitialTransition(s);
}
