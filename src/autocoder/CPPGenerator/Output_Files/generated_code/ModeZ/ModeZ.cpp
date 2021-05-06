#include "ModeZ.h"
#include "../HSMState/HSMState.h"
#include "../HSM/HSM.h"
#include "../UserObjects/bsp.hpp"
#include "../on/on.h"

#include <iostream>
HSMState * ModeZ::_self = NULL; 
//Constructor
ModeZ::ModeZ() {
    std::cout << "ModeZ Constructed" << std::endl;
}

//Entry Functions
void ModeZ::Entry() {
    std::cout << "Entered ModeZ State" << std::endl;
    BSP::ledBlue();
}

//Exit Functions
void ModeZ::Exit() {
    std::cout << "Exited ModeZ State" << std::endl;
}

//Transitions
void ModeZ::LOOP_EVENT() {

    HSMState::ChangeState(this->_context, on::Instance());
}
