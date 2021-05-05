#include "qpcpp.hpp" // QP/C++ framework API
#include "bsp.hpp"   // Board Support Package interface

using namespace QP;

// the main function ---------------------------------------------------------
int main() {
    QF::init();  // initialize the framework
    BSP::init(); // initialize the BSP

    // start the Blinky active object
    static QEvt const *blinky_queueSto[10]; // event queue buffer for Blinky
    AO_Blinky->start(1U, // priority of the active object
        blinky_queueSto, // event queue buffer
        Q_DIM(blinky_queueSto), // the length of the buffer
        (void *)0, 0U);  // private stack (not used on the desktop)

    return QF::run(); // let the framework run the application
}