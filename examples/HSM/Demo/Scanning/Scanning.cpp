#include "Scanning.h"
#include "../HSMState/HSMState.h"
#include "../HSM/HSM.h"
#include "../UserObjects/bsp.hpp"
#include "../Active/Active.h"
#include "../ModeZ/ModeZ.h"

#include <iostream>
HSMState * Scanning::_self = NULL; 
//Constructor
Scanning::Scanning() {
    std::cout << "Scanning Constructed" << std::endl;
}

//Entry Functions
void Scanning::Entry() {
    std::cout << "Entered Scanning State" << std::endl;
    BSP::ledOn();
}

//Exit Functions
void Scanning::Exit() {
    std::cout << "Exited Scanning State" << std::endl;
}

//Transitions
void Scanning::TIMEOUT() {

    HSMState::ChangeState(this->_context, Active::Instance());
}
                
//Junctions

void Scanning::JUNCTION_EVENT() {

   if(this->_context->flag == 1) {
       BSP::makeEvilNoise();
       HSMState::ChangeState(this->_context, Active::Instance());
   }
   else {

       
       HSMState::ChangeState(this->_context, ModeZ::Instance());
   }
}
