#include "bsp.hpp"    // Board Support Package interface
#include <iostream>   // for cout/cerr
#include <cstdlib>    // for exit()

using namespace std;

void BSP::init(void)   {
    cout << "Simple Blinky example\nQP/C++ version: "
         << "\nPress Ctrl-C to quit..."
         << endl; // print QP version
}
void BSP::ledOff(void) { cout << "LED OFF" << endl; }
void BSP::ledOn(void)  { cout << "LED ON" << endl;  }
void BSP::ledRed(void) { cout << "LED RED" << endl; }
void BSP::ledGreen(void) { cout << "LED GREEN" << endl; }
void BSP::ledBlue(void) { cout << "LED BLUE" << endl; }
void BSP::makeNoise(void)  { cout << "BEEP BOOP" << endl;  }
void BSP::makeEvilNoise(void)  { cout << "MUAH HA HA" << endl;  }







