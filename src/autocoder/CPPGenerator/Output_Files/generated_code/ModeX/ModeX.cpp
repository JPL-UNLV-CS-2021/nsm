#include "ModeX.h"
#include "../HSMState/HSMState.h"
#include "../HSM/HSM.h"
#include "../UserObjects/bsp.hpp"
#include "../off/off.h"

#include <iostream>
HSMState * ModeX::_self = NULL; 
//Constructor
ModeX::ModeX() {
    std::cout << "ModeX Constructed" << std::endl;
}

//Entry Functions
void ModeX::Entry() {
    std::cout << "Entered ModeX State" << std::endl;
    BSP::ledRed();
}

//Exit Functions
void ModeX::Exit() {
    std::cout << "Exited ModeX State" << std::endl;
}

//Transitions
void ModeX::TIMEOUT() {

    HSMState::ChangeState(this->_context, off::Instance());
}
