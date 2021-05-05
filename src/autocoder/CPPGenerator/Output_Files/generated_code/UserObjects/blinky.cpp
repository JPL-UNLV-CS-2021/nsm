#include "qpcpp.hpp" // QP/C++ framework API
#include "bsp.hpp"   // Board Support Package interface

using namespace QP;

// ask QM to declare the Blinky class ----------------------------------------
$declare${AOs::Blinky}

// opaque pointer to the Blinky active object --------------------------------
$define${AOs::AO_Blinky}

// ask QM to define the Blinky class (including the state machine) -----------
$define${AOs::Blinky}