
#ifndef HSM_
#define HSM_
#include "../HSMState/HSMState.h"
#include <iostream>
#include <string>
#define H_LEVEL 3

class HSMState;

class HSM {
public:
    HSM();
    void Initialize();
    std::string getCurrentState();

    //A list of all events in the system
    void OFF();
    void TIMEOUT();
    void PEDESTRIAN_WAITING();

    //Global Vars
    bool isPedestrianWaiting;
    int  pedestrianFlashCtr;


    //State Design
    HSMState* _state;
    friend class HSMState;
    void ChangeState(HSMState*);
    void HandleEntryExit(HSMState*, HSMState*);
    //CallStacks
    //The length of these arrays is equal to
    //the height of the heirarchial state machine
    HSMState* entryStates[H_LEVEL];
    HSMState* exitStates[H_LEVEL];
    int numOfEntryStates;
    int numOfExitStates;
    HSMState* commonParent;

    bool running;
    void setRunning(bool b) { running = b; };
    bool isRunning() { return running; }

    bool timeFlag;
    void setTimeFlag(bool tf) { timeFlag = tf; };
    bool getTimeFlag() { return timeFlag; }

    int timeStart = 0;
    void setTimeStart(int ts) { timeStart = ts; };
    int getTimeStart() { return timeStart; }

    int clock = 2;
    void tick() { clock++; };
    int getGlobalTime() { return clock; };

    int timeLimit = 0;
    void setTimeLimit(int tl) { timeLimit = tl; };
    int getTimeLimit() { return timeLimit; };

    void killTimer() {
        timeFlag = false;
        timeStart = getGlobalTime();
        timeLimit = 0;
    };

    void setTimer() {
        std::cout << "setTimer Called gtime = " << getGlobalTime() << std::endl;
        timeFlag = true;
        setTimeStart(getGlobalTime());
        timeLimit = 5;
    };

};

#endif 
