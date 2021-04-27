#include "HSMState.h"

HSMState::HSMState() {
}

void HSMState::ChangeState(HSM* t, HSMState* s) {
    t->ChangeState(s);
}

void HSMState::InitialTransition(HSM* t, HSMState* s) {
    t->InitialTransition(s);
}
