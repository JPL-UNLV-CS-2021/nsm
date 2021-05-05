#include "pedestriansWalk.h"
#include "../HSMState/HSMState.h"
#include "../HSM/HSM.h"
#include "../pedestriansFlash/pedestriansFlash.h"
#include <iostream>

HSMState* pedestriansWalk::_self = NULL;
pedestriansWalk::pedestriansWalk() {
    //std::cout << "pedestriansWalk Constructed" << std::endl;
}

void pedestriansWalk::Entry() {
    //std::cout << "Entered pedestriansWalk State" << std::endl;
    //std::cout << "SetTimer()" << std::endl;
    this->_context->setTimer();
    //std::cout << "signalPedestrians(WALK)" << std::endl;
}


void pedestriansWalk::Exit() {
    //std::cout << "Exited pedestriansWalk State" << std::endl;
    //std::cout << "KillTimer()" << std::endl;
    this->_context->killTimer();
}


void pedestriansWalk::TIMEOUT() {
    HSMState::ChangeState(this->_context, pedestriansFlash::Instance());
}
