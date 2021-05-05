#include "pedestriansEnabled.h"
#include "../HSM/HSM.h"
#include "../HSMState/HSMState.h"
#include "../pedestriansWalk/pedestriansWalk.h"
#include <iostream>

HSMState* pedestriansEnabled::_self = NULL;
pedestriansEnabled::pedestriansEnabled() {
    //std::cout << "pedestriansEnabled Constructed" << std::endl;
}

void pedestriansEnabled::Entry() {
    //std::cout << "Entered pedestriansEnabled State" << std::endl;
    //std::cout << "signalVehicles(RED);" << std::endl;
    //HSMState::InitialTransition(this->_context, pedestriansWalk::Instance());
}

void pedestriansEnabled::Exit() {
    //std::cout << "Exited pedestriansEnabled State" << std::endl;
}

