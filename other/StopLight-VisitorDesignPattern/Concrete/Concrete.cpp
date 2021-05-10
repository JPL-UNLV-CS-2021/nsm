#ifndef Concrete_
#define Concrete_
#include <iostream>
#include "../Abstract/Abstract.h"
#include "../global.h"

using namespace std;

/*
    Implement the Accept function for each class
    Rev1 - Implemented functions
    Rev2 - Changed return type to void, passed state machine to reference which state we're in at any given point from the
            visit function
*/

// The transition function will dynamically cast the pointer of the current state to one of these types, based on whatever is needed.
// Then, one of these functions will call its visit function, which will change the pointer to the new state that we transition to.
void State::Accept(Visitor* tr) { return tr->Visit(this); };
void Operational::Accept(EntryVisitor* tr, SM &machine) { return tr->Visit(this, machine); };
void VehiclesEnabled::Accept(EntryVisitor* tr, SM& machine) { return tr->Visit(this, machine); };
void VehiclesGreen::Accept(EntryVisitor* tr, SM& machine) { return tr->Visit(this, machine); };
void VehiclesGreenInt::Accept(EntryVisitor* tr, SM& machine) { return tr->Visit(this, machine); };
void VehiclesYellow::Accept(EntryVisitor* tr, SM& machine) { return tr->Visit(this, machine); };
void PedestriansEnabled::Accept(EntryVisitor* tr, SM& machine) { return tr->Visit(this, machine); };
void PedestriansWalk::Accept(EntryVisitor* tr, SM& machine) { return tr->Visit(this, machine); };
void PedestriansFlash::Accept(EntryVisitor* tr, SM& machine) { return tr->Visit(this, machine); };
void Off::Accept(EntryVisitor* tr, SM& machine) { return tr->Visit(this, machine); };

/*
    Implement the Constructor for each class to set state names
*/
Operational::Operational(string n) { SetName(n); SetType("Operational"); };
VehiclesEnabled::VehiclesEnabled(string n) { SetName(n); SetType("VehiclesEnabled"); };
VehiclesGreen::VehiclesGreen(string n) { SetName(n); };
VehiclesGreenInt::VehiclesGreenInt(string n) { SetName(n); };
VehiclesYellow::VehiclesYellow(string n) { SetName(n); };
PedestriansEnabled::PedestriansEnabled(string n) { SetName(n); };
PedestriansWalk::PedestriansWalk(string n) { SetName(n); };
PedestriansFlash::PedestriansFlash(string n) { SetName(n); };
Off::Off(string n) { SetName(n); };

/*
    Implement the Visit function for each class.
    The machine is passed by reference, and the state is changed to the state that we visit.
    This is done because we must reference the ACTUAL object that implements the state.
    Otherwise, if we were to return the type that we visit and have the state changed that way, we would only
    be modifying a temporary pointer. When the visit function ends, the pointer would no longer exist.
    This took us 3 days to solve.
*/
void Visitor::Visit(State* state) {
    cout << "Unknown event, reporting and ignoring.\n";
}
void EntryVisitor::Visit(Operational* state, SM& machine) {
    cout << "Called entry action on  Operational. Setting state to VehiclesEnabled\n";
    machine.SetState(machine.vehiclesEnabled);
}
void EntryVisitor::Visit(VehiclesEnabled* state, SM& machine) {
    cout << "Called entry action on  VisitVehiclesEnabled\n";
    machine.SetState(machine.vehiclesGreen);
}
void EntryVisitor::Visit(VehiclesGreen* state, SM& machine) {
    cout << "Called entry action on  VisitVehiclesGreen\n";
    machine.SetState(machine.vehiclesGreenInt);
}
void EntryVisitor::Visit(VehiclesGreenInt* state, SM& machine) {
    cout << "Called entry action on  VisitVehiclesGreenInt\n";
    machine.SetState(machine.vehiclesYellow);
}
void EntryVisitor::Visit(VehiclesYellow* state, SM& machine) {
    cout << "Called entry action on  VisitVehiclesYellow\n";
    machine.SetState(machine.pedestriansEnabled);
}
void EntryVisitor::Visit(PedestriansEnabled* state, SM& machine) {
    cout << "Called entry action on  VisitPedestriansEnabled\n";
    machine.SetState(machine.pedestriansWalk);
}
void EntryVisitor::Visit(PedestriansWalk* state, SM& machine) {
    cout << "Called entry action on  VisitPedestriansWalk\n";
    machine.SetState(machine.pedestriansFlash);
}
void EntryVisitor::Visit(PedestriansFlash* state, SM& machine) {
    cout << "Called entry action on  VisitPedestriansFlash\n";
    machine.SetState(machine.off);
}
void EntryVisitor::Visit(Off* state, SM& machine) {
    cout << "Called entry action on  VisitOff\n";
    machine.SetState(machine.operational);
}
#endif
