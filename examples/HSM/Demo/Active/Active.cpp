#include "Active.h"
#include "../HSMState/HSMState.h"
#include "../HSM/HSM.h"
#include "../UserObjects/bsp.hpp"
#include "../Scanning/Scanning.h"

#include <iostream>
HSMState * Active::_self = NULL; 
//Constructor
Active::Active() {
    std::cout << "Active Constructed" << std::endl;
}

//Entry Functions
void Active::Entry() {
    std::cout << "Entered Active State" << std::endl;
    BSP::ledOff();
    this->_context->flag = 0;
}

//Exit Functions
void Active::Exit() {
    std::cout << "Exited Active State" << std::endl;
}

//Transitions
void Active::TIMEOUT() {

    HSMState::ChangeState(this->_context, Scanning::Instance());
}
