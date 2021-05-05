#include "Operational.h"
#include "../Off/Off.h"
#include "../vehiclesEnabled/vehiclesEnabled.h"
#include <iostream>

HSMState* Operational::_self = NULL;

Operational::Operational() {
    //std::cout << "Operational Constructed" << std::endl;

}

void Operational::Entry() {
    //std::cout << "Entered Operational State" << std::endl;

    //InitialTransition(this->_context, vehiclesEnabled::Instance());
}

void Operational::Exit() {
    //std::cout << "Exited Operational State" << std::endl;
}


void Operational::OFF() {
    ChangeState(this->_context, Off::Instance());
}