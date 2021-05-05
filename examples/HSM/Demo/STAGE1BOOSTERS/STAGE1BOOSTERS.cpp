#include "STAGE1BOOSTERS.h"
#include "../HSMState/HSMState.h"
#include "../HSM/HSM.h"
#include "../UserObjects/bsp.hpp"
#include "../Scanning/Scanning.h"

#include <iostream>
HSMState * STAGE1BOOSTERS::_self = NULL; 
//Constructor
STAGE1BOOSTERS::STAGE1BOOSTERS() {
    std::cout << "STAGE1BOOSTERS Constructed" << std::endl;
}

//Entry Functions
void STAGE1BOOSTERS::Entry() {
    std::cout << "Entered STAGE1BOOSTERS State" << std::endl;
}

//Exit Functions
void STAGE1BOOSTERS::Exit() {
    std::cout << "Exited STAGE1BOOSTERS State" << std::endl;
}

//Transitions
void STAGE1BOOSTERS::TIMEOUT() {
BSP::ledOff();
    HSMState::ChangeState(this->_context, Scanning::Instance());
}
