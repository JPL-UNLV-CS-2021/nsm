#include "on.h"
#include "../HSMState/HSMState.h"
#include "../HSM/HSM.h"
#include "../UserObjects/bsp.hpp"
#include "../off/off.h"
#include "../ModeZ/ModeZ.h"

#include <iostream>
HSMState * on::_self = NULL; 
//Constructor
on::on() {
    std::cout << "on Constructed" << std::endl;
}

//Entry Functions
void on::Entry() {
    std::cout << "Entered on State" << std::endl;
    BSP::ledOn();
}

//Exit Functions
void on::Exit() {
    std::cout << "Exited on State" << std::endl;
}

//Transitions
void on::TIMEOUT() {

    HSMState::ChangeState(this->_context, off::Instance());
}
                
//Junctions

void on::JUNCTION_EVENT() {

   if(this->_context->flag == 1) {
       BSP::makeEvilNoise();
       HSMState::ChangeState(this->_context, off::Instance());
   }
   else {

       
       HSMState::ChangeState(this->_context, ModeZ::Instance());
   }
}
