#include "vehiclesYellow.h"
#include "../HSM/HSM.h"
#include "../HSMState/HSMState.h"
#include "../pedestriansWALK/pedestriansWALK.h"
#include <iostream>

HSMState* vehiclesYellow::_self = NULL;
vehiclesYellow::vehiclesYellow() {
    //std::cout << "vehiclesYellow Constructed" << std::endl;
}

void vehiclesYellow::Entry() {
    //std::cout << "Entered vehiclesYellow State" << std::endl;
    //std::cout << "SetTimer()" << std::endl;
    this->_context->setTimer();
    //std::cout << "SignalVehicles(Yellow)" << std::endl;
}


void vehiclesYellow::Exit() {
    //std::cout << "Exited vehiclesYellow State" << std::endl;
    //std::cout << "KillTimer()" << std::endl;
    this->_context->killTimer();
}




void vehiclesYellow::TIMEOUT() {
    HSMState::ChangeState(this->_context, pedestriansWalk::Instance());
}
