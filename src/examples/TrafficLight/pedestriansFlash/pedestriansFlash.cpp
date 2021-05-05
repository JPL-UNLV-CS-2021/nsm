#include "pedestriansFlash.h"
#include "../HSM/HSM.h"
#include "../HSMState/HSMState.h"
#include "../vehiclesEnabled/vehiclesEnabled.h"
#include "../vehiclesGreen/vehiclesGreen.h"
#include <iostream>

HSMState* pedestriansFlash::_self = NULL;
pedestriansFlash::pedestriansFlash() {
    //std::cout << "pedestriansFlash Constructed" << std::endl;
}

void pedestriansFlash::Entry() {
    //std::cout << "Entered pedestriansFlash State" << std::endl;
    //std::cout << "SetTimer()" << std::endl;
    this->_context->setTimer();
    this->_context->pedestrianFlashCtr = 7;
}


void pedestriansFlash::Exit() {
    //std::cout << "Exited pedestriansFlash State" << std::endl;
}





void pedestriansFlash::TIMEOUT() {

    //std::cout << "KillTimer()" << std::endl;
    this->_context->killTimer();
    this->_context->pedestrianFlashCtr--;
    if (this->_context->pedestrianFlashCtr == 0) {
        HSMState::ChangeState(this->_context, vehiclesGreen::Instance());
    }
    else if ((this->_context->pedestrianFlashCtr & 1) == 0) {
        //std::cout << "signalPedestians(DONT_WALK);" << std::endl;
        pedestriansFlash::DynamicEntry();
    }
    else {
        //std::cout << "signalPedestians(BLANK);" << std::endl;
        pedestriansFlash::DynamicEntry();
    }
}

void pedestriansFlash::DynamicEntry() {
    //std::cout << "Dynamic Entry pedestriansFlash State" << std::endl;
    //std::cout << "SetTimer()" << std::endl;

    this->_context->setTimer();
}