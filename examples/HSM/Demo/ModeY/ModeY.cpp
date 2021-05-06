#include "ModeY.h"
#include "../HSMState/HSMState.h"
#include "../HSM/HSM.h"
#include "../UserObjects/bsp.hpp"

#include <iostream>
HSMState * ModeY::_self = NULL; 
//Constructor
ModeY::ModeY() {
    std::cout << "ModeY Constructed" << std::endl;
}

//Entry Functions
void ModeY::Entry() {
    std::cout << "Entered ModeY State" << std::endl;
    BSP::ledGreen();
    this->_context->flag = 1;
}

//Exit Functions
void ModeY::Exit() {
    std::cout << "Exited ModeY State" << std::endl;
}

//Transitions
