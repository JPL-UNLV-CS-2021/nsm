#include <iostream>
#include "StateMachine.h"

using namespace std;

int main(int argc, char **argv) {

    cout << "Starting State Machine" << endl;

    StateMachine sm;

    sm.Run();

    cout << "State Machine Complete" << endl;

    return 0;
}


