// An implementation of a State Machine using the Visitor Design Pattern
// Written by Edgar Amalyan and Stephen Baker.

#include <iostream>
#include "global.h"
#include "Abstract/Abstract.h"
using namespace std;

//void Transition(SM &machine, EntryVisitor& v) {
//    //Operational* c = dynamic_cast<Operational*>((machine.globalState));
//    cout << "Starting transition from " << machine.GetState()->GetName() << "." << endl;
//    if (machine.GetState()->GetType() == "Operational") {
//        machine.SetState(dynamic_cast<Operational*>(machine.GetState()));
//        dynamic_cast<Operational*>(machine.GetState())->Accept(v);
//    }
//}

int main(int argc, char** argv) {
    cout << "Hello, World - Edgar/Stephen" << std::endl;

    // Declare all states and visitor actions
    EntryVisitor entry;

    // Create the machine with a default state
    SM machine("Traffic Light Example");
    machine.SetDefault(); // Sets the default. Will be parsed and code generated from XML

    // Perform some transitions as a test
    machine.Transition(&entry);
    machine.Transition(&entry);
    machine.Transition(&entry);

    return 0;
}
