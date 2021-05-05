
#include "vehiclesGreenInt.h"
#include "../HSM/HSM.h"
#include "../HSMState/HSMState.h"
#include "../vehiclesYellow/vehiclesYellow.h"
#include <iostream>


HSMState* vehiclesGreenInt::_self = NULL;
vehiclesGreenInt::vehiclesGreenInt() {
    //std::cout << "vehiclesGreenInt Constructed" << std::endl;
}

void vehiclesGreenInt::Entry() {
    //std::cout << "Entered vehiclesGreenInt State" << std::endl;
}


void vehiclesGreenInt::Exit() {
    //std::cout << "Exited vehiclesGreenInt State" << std::endl;

}



void vehiclesGreenInt::PEDESTRIAN_WAITING() {

    HSMState::ChangeState(this->_context, vehiclesYellow::Instance());
}