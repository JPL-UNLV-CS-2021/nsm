#ifndef Abstract_
#define Abstract_
#include <iostream>
using namespace std;

/*
    Declare base class "State" for others to inherit from
    This class represents a state in the state machine.
*/
// Prototypes
class State;
class Visitor;
class SM;
class EntryVisitor;
class Operational;
class VehiclesEnabled;

class State {
public:
    virtual ~State() {};
    State() {};
    State(string n) { // Constructor to set the name
        name = n;
    }
    virtual void Accept(Visitor *tr);
    void SetName(string n) {
        name = n;
    };
    string GetName() {
        return name;
    };
    string GetType() {
        return type; // Used for dynamic cast
    }
    void SetType(string t) {
        type = t; // Used for dynamic cast
    }
    virtual void test() {};
private:
    string name;
    string type;
};

/*
    Declare base class "Event" for others to inherit from
    Implemented in concrete.cpp
*/
class Visitor {
public:
    ~Visitor() {};
    void Visit(State* state);
};


// Declare concrete states
// Implemented in concrete.cpp
// A current goal here is to make the states better represent a hierarchy.
// JPL said that they would like if a user could understand the hierarchy of the state machine from the generated C++ code.
class Operational : public State {
public:
    Operational() {};
    Operational(string n);
    void Accept(EntryVisitor* tr, SM &machine) ;
    Operational* GetThis() {
        return this;
    }
};
class VehiclesEnabled : public State {
public:
    VehiclesEnabled(string n);
    void Accept(EntryVisitor* tr, SM& machine) ;
};
class VehiclesGreen : public State {
public:
    VehiclesGreen(string n);
    void Accept(EntryVisitor* tr, SM& machine);
};
class VehiclesGreenInt: public State {
public:
    VehiclesGreenInt(string n);
    void Accept(EntryVisitor* tr, SM& machine) ;
};
class VehiclesYellow : public State {
public:
    VehiclesYellow(string n);
    void Accept(EntryVisitor* tr, SM& machine) ;
};
class PedestriansEnabled : public State {
public:
    PedestriansEnabled(string n);
    void Accept(EntryVisitor* tr, SM& machine);
};
class PedestriansWalk : public State {
public:
    PedestriansWalk(string n);
    void Accept(EntryVisitor* tr, SM& machine) ;
};
class PedestriansFlash : public State {
public:
    PedestriansFlash(string n);
    void Accept(EntryVisitor* tr, SM& machine) ;
};
class Off : public State {
public:
    Off(string n);
    void Accept(EntryVisitor* tr, SM& machine) ;
};

class EntryVisitor : public Visitor {
public:
    void Visit(Operational* state, SM &machine);
    void Visit(VehiclesEnabled* state, SM &machine);
    void Visit(VehiclesGreen* state, SM &machine);
    void Visit(VehiclesGreenInt* state, SM &machine);
    void Visit(VehiclesYellow* state, SM &machine);
    void Visit(PedestriansEnabled* state, SM &machine);
    void Visit(PedestriansWalk* state, SM &machine);
    void Visit(PedestriansFlash* state, SM &machine);
    void Visit(Off* state, SM &machine);
};


/*
    Declare the machine itself to track current state
*/
class SM {

public:
    ~SM() {};
    SM(string n) { // Constructor of SM
        name = n;
        cout << "Created a new state machine '" << name << "'.\n";
    };
    State* GetState() {
        return globalState;
    }
    void SetState(State &s) {
        globalState = &s;
    };
    // This is the transition function that performs a state transition from the current state to the new state;
    // The new state is decided by the specific event.
    void Transition(EntryVisitor* v) {
        cout << "Starting transition from " << globalState->GetName() << "." << endl;
        // To have the correct Accept function in concrete.cpp selected, type casting must be performed.
        // This is because the pointer, globalState, is of the base class type. If we use it without type casting, the Accept function
        // that is of type State in concrete.cpp will be selected. This means that we will never transition.
        // Therefore, we must cast it to the proper type. This is done using a string that is built into the derived class.
        // This works for a small number of states, but if there are 1000 states, then there will be up to 1000 searches to find the correct type.
        // As of now, we are trying to find an efficient way to get the type and dynamically cast it (as C++ is strongly typed).
        // Current ideas include a hash table or some pointer manipulation using the "this" pointer.
        if (globalState->GetType() == "Operational")
            ((Operational*)globalState)->Accept(v, *this);
        else if(globalState->GetType() == "VehiclesEnabled")
            ((VehiclesEnabled*)globalState)->Accept(v, *this);
        else if(globalState->GetType() == "VehiclesGreen")
            ((VehiclesGreen*)globalState)->Accept(v, *this);
        else if(globalState->GetType() == "VehiclesGreenInt")
            ((VehiclesGreenInt*)globalState)->Accept(v, *this);
        else if(globalState->GetType() == "VehiclesYellow")
            ((VehiclesGreen*)globalState)->Accept(v, *this);
        else if(globalState->GetType() == "PedestriansEnabled")
            ((PedestriansEnabled*)globalState)->Accept(v, *this);
        else if(globalState->GetType() == "PedestriansWalk")
            ((PedestriansWalk*)globalState)->Accept(v, *this);
        else if(globalState->GetType() == "PedestriansFlash")
            ((PedestriansFlash*)globalState)->Accept(v, *this);
        else if(globalState->GetType() == "Off")
            ((Off*)globalState)->Accept(v, *this);
        else
            globalState->Accept(v);
    }
    void SetDefault() { // User can select the default state of the machine
        globalState = &operational;
    }
    // All of the states are members of the SM class.
    Operational operational = Operational("Operational");
    VehiclesEnabled vehiclesEnabled = VehiclesEnabled("vehiclesEnabled");
    VehiclesGreen vehiclesGreen = VehiclesGreen("vehiclesGreen");
    VehiclesGreenInt vehiclesGreenInt = VehiclesGreenInt("VehiclesGreenInt");
    VehiclesYellow vehiclesYellow = VehiclesYellow("VehiclesYellow");
    PedestriansEnabled pedestriansEnabled = PedestriansEnabled("PedestriansEnabled");
    PedestriansWalk pedestriansWalk = PedestriansWalk("PedestriansWalk");
    PedestriansFlash pedestriansFlash = PedestriansFlash("PedestriansFlash");
    Off off = Off("Off");
private:
    State* globalState; // A pointer to the current state
    string name;
};

#endif

