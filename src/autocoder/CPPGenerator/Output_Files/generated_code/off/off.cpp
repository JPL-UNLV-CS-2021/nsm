#include "off.h"
#include "../HSMState/HSMState.h"
#include "../HSM/HSM.h"
#include "../UserObjects/bsp.hpp"
#include "../on/on.h"

#include <iostream>
HSMState * off::_self = NULL; 
//Constructor
off::off() {
    std::cout << "off Constructed" << std::endl;
}

//Entry Functions
void off::Entry() {
    std::cout << "Entered off State" << std::endl;
    BSP::ledOff();
    this->_context->flag = 0;
}

//Exit Functions
void off::Exit() {
    std::cout << "Exited off State" << std::endl;
}

//Transitions
void off::TIMEOUT() {

    HSMState::ChangeState(this->_context, on::Instance());
}
