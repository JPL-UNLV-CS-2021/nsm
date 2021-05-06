#include "HSM.h"
#include "../off/off.h"
#include "../on/on.h"
#include "../ModeZ/ModeZ.h"
#include "../ModeY/ModeY.h"
#include "../ModeX/ModeX.h"
HSM::HSM() {

}
void HSM::Initialize() {

setRunning(true);
setTimeFlag(false);

    static off A;
	A._self = &A;
	A._context = this;
	A.level = 0;
	A._parent = NULL;
	A.stateName = "off";
	    static on B;
	B._self = &B;
	B._context = this;
	B.level = 0;
	B._parent = NULL;
	B.stateName = "on";
	    static ModeX E;
	E._self = &E;
	E._context = this;
	E.level = 0;
	E._parent = NULL;
	E.stateName = "ModeX";
	    static ModeY D;
	D._self = &D;
	D._context = this;
	D.level = 1;
	D._parent = &E;
D.stateName = "ModeY";
	    static ModeZ C;
	C._self = &C;
	C._context = this;
	C.level = 2;
	C._parent = &D;
C.stateName = "ModeZ";
	this->_state = off::Instance();
   this->_state->Entry();
}


void HSM::TIMEOUT() {
   _state->TIMEOUT();
}


void HSM::JUNCTION_EVENT() {
   _state->JUNCTION_EVENT();
}


void HSM::LOOP_EVENT() {
   _state->LOOP_EVENT();
}


std::string HSM::getCurrentState() {
   return _state->stateName;
}

void HSM::ChangeState(HSMState* s) {

	HandleEntryExit(_state, s);

	for (int i = 0; i < numOfExitStates; i++) {
		exitStates[i]->Exit();
	}

	_state = s;
	for (int i = numOfEntryStates - 1; i >= 0; i--) {
		entryStates[i]->Entry();
}

}void HSM::HandleEntryExit(HSMState * FROM, HSMState * TO) {
	HSMState* fromOriginal = FROM;
	HSMState* toOriginal = TO;
	numOfEntryStates = 0;
	numOfExitStates = 0;
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

	while (FROM != TO) {
		exitStates[numOfExitStates] = FROM;
		numOfExitStates++;
		FROM = FROM->_parent;
		entryStates[numOfEntryStates] = TO;
		numOfEntryStates++;
		TO = TO->_parent; 
	}
	commonParent = TO;
	FROM = fromOriginal;
	TO = toOriginal;
}

