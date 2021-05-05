#include "vehiclesEnabled.h"
#include "../HSMState/HSMState.h"
#include "../HSM/HSM.h"
#include "../vehiclesGreen/vehiclesGreen.h"
#include <iostream>

HSMState* vehiclesEnabled::_self = NULL;

vehiclesEnabled::vehiclesEnabled() {
    //std::cout << "vehiclesEnabled Constructed" << std::endl;
}

void vehiclesEnabled::Entry() {
    //std::cout << "Entered vehiclesEnabled State" << std::endl;
    //std::cout << "signalPedestrians(DONT_WALK);" << std::endl;
}

void vehiclesEnabled::Exit() {
    //std::cout << "Exited vehiclesEnabled State" << std::endl;
}


