#include "vehiclesGreen.h"
#include "../HSMState/HSMState.h"
#include "../HSM/HSM.h"
#include "../vehiclesYellow/vehiclesYellow.h"
#include "../vehiclesGreenInt/vehiclesGreenInt.h"
#include <iostream>
HSMState* vehiclesGreen::_self = NULL;
vehiclesGreen::vehiclesGreen() {
    //std::cout << "vehiclesGreen Constructed" << std::endl;
}

void vehiclesGreen::Entry() {
    //std::cout << "Entered vehiclesGreen State" << std::endl;
    //std::cout << "SetTimer()" << std::endl;
    this->_context->setTimer();


    //std::cout << "SignalVehicles(GREEN)" << std::endl;
    this->_context->isPedestrianWaiting = false;
}


void vehiclesGreen::Exit() {
    //std::cout << "Exited vehiclesGreen State" << std::endl;
    //std::cout << "KillTimer()" << std::endl;
    this->_context->killTimer();
}


void vehiclesGreen::PEDESTRIAN_WAITING() {
    this->_context->isPedestrianWaiting = true;
}

void vehiclesGreen::TIMEOUT() {

    if (this->_context->isPedestrianWaiting) {
        HSMState::ChangeState(this->_context, vehiclesYellow::Instance());
    }
    else {

        HSMState::ChangeState(this->_context, vehiclesGreenInt::Instance());
    }
}
