
#include "HSM.h"
#include "../Off/Off.h"
#include "../Operational/Operational.h"
#include "../pedestriansEnabled/pedestriansEnabled.h"
#include "../pedestriansFlash/pedestriansFlash.h"
#include "../pedestriansWalk/pedestriansWalk.h"
#include "../vehiclesEnabled/vehiclesEnabled.h"
#include "../vehiclesGreen/vehiclesGreen.h"
#include "../vehiclesGreenInt/vehiclesGreenInt.h"
#include "../vehiclesYellow/vehiclesYellow.h"

#include <string>


HSM::HSM() {
    isPedestrianWaiting = false;
    pedestrianFlashCtr = -1;
    //INIT ALL STATES
}


void HSM::Initialize() {

    setRunning(true);
    setTimeFlag(false);

    static Off a;
    a._self = &a;
    a._context = this;
    a.level = 0;
    a._parent = NULL;
    a.stateName = "Off";
    static Operational b;
    b._self = &b;
    b._context = this;
    b.level = 0;
    b._parent = NULL;
    b.stateName = "Operational";
    static pedestriansEnabled c;
    c._self = &c;
    c._context = this;
    c.level = 1;
    c._parent = &b;
    c.stateName = "pedestriansEnabled";
    static pedestriansFlash d;
    d._self = &d;
    d._context = this;
    d.level = 2;
    d._parent = &c;
    d.stateName = "pedestriansFlash";
    static pedestriansWalk e;
    e._self = &e;
    e._context = this;
    e.level = 2;
    e._parent = &c;
    e.stateName = "pedestriansWalk";
    static vehiclesEnabled f;
    f._self = &f;
    f._context = this;
    f.level = 1;
    f._parent = &b;
    f.stateName = "vehiclesEnabled";
    static vehiclesGreen g;
    g._self = &g;
    g._context = this;
    g.level = 2;
    g._parent = &f;
    g.stateName = "vehiclesGreen";
    static vehiclesGreenInt h;
    h._self = &h;
    h._context = this;
    h.level = 2;
    h._parent = &f;
    h.stateName = "vehiclesGreenInt";
    static vehiclesYellow i;
    i._self = &i;
    i._context = this;
    i.level = 2;
    i._parent = &f;
    i.stateName = "vehiclesYellow";


    //this->_state = Operational::Instance();
    //Hacky way to deal with system start up
    this->_state = Operational::Instance();
    _state->Entry();

    this->_state = vehiclesEnabled::Instance();
    _state->Entry();

    this->_state = vehiclesGreen::Instance();
    _state->Entry();

}

void HSM::ChangeState(HSMState* s) {

    //This function fills entry and exit array
    HandleEntryExit(_state, s);

    for (int i = 0; i < numOfExitStates; i++) {
        exitStates[i]->Exit();
    }

    //while (_state->level >= commonParent->level) {
    //    _state->Exit();
    //    if (_state->_parent == NULL) {
    //        break;
    //    }
    //    _state = _state->_parent;
    //}
    //_state->Exit();
    _state = s;

    for (int i = numOfEntryStates - 1; i >= 0; i--) {
        entryStates[i]->Entry();
    }

    //_state->Entry();
}

std::string HSM::getCurrentState() {
    return _state->stateName;
}

void HSM::HandleEntryExit(HSMState* FROM, HSMState* TO) {
    HSMState* fromOriginal = FROM;
    HSMState* toOriginal = TO;
    numOfEntryStates = 0;
    numOfExitStates = 0;
    //Check current Levels
    while (FROM->level != TO->level) {
        if (FROM->level > TO->level) {

            exitStates[numOfExitStates] = FROM;
            numOfExitStates++;
            FROM = FROM->_parent;
        }
        else {

            entryStates[numOfEntryStates] = TO;
            numOfEntryStates++;
            TO = TO->_parent;
        }
    }

    // At this point both states are on same level
    //     0
    //    /|\
    //   0 0 0 <-

    while (FROM != TO) {

        exitStates[numOfExitStates] = FROM;
        numOfExitStates++;
        FROM = FROM->_parent;

        entryStates[numOfEntryStates] = TO;
        numOfEntryStates++;
        TO = TO->_parent;
    }

    commonParent = TO; //Could use either TO or FROM

    FROM = fromOriginal;
    TO = toOriginal;

}

void HSM::OFF() {
    _state->OFF();
}

void HSM::TIMEOUT() {
    _state->TIMEOUT();
}

void HSM::PEDESTRIAN_WAITING() {
    _state->PEDESTRIAN_WAITING();
}

