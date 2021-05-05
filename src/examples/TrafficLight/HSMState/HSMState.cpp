#include "HSMState.h"
#include <thread>
#include <chrono>

using namespace std;

HSMState::HSMState() {
}

void HSMState::ChangeState(HSM* t, HSMState*  s) {
    t->ChangeState(s);
}

