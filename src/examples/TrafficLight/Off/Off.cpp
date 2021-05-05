
#include "../HSMState/HSMState.h"
#include "Off.h"
#include <iostream>


HSMState* Off::_self = NULL;

Off::Off() {
    //std::cout << "Off Constructed" << std::endl;
    
}

void Off::Entry() {
    //std::cout << "Entered Off State" << std::endl;
    //std::cout << "Shutdown()" << std::endl;
    //Set flag in context to exit main loop
}

void Off::Exit() {
    //std::cout << "Exited Off State" << std::endl;
    
    this->_context->setRunning(false);
}

