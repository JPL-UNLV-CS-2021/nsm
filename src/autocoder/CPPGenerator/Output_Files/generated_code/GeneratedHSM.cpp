#include "HSM/HSM.h"
#include <iostream>
#include <thread>
#include <chrono>
#include "Event/Event.h"
#include <queue>
#include <map>
#include <fstream>
#include <iomanip>
#include <direct.h>
#define GetCurrentDir _getcwd
using namespace std;

typedef void (HSM::*stateEventHandler)(void);
typedef std::map<std::string, stateEventHandler> state_func_map_t;
bool parseEventsFromInput(queue<Event>&, string);
bool dispatch(state_func_map_t , Event , HSM& );

int main(int argc, char** argv) {
    queue<Event> events;
    parseEventsFromInput(events, argv[1]);
    state_func_map_t m;

    m["TIMEOUT"] = &HSM::TIMEOUT;
    m["JUNCTION_EVENT"] = &HSM::JUNCTION_EVENT;
    m["LOOP_EVENT"] = &HSM::LOOP_EVENT;


    cout << "**********QSM**********\n"
         << "-----------------------" << std::endl;
    static HSM hsm;
    hsm.Initialize();

    while (hsm.isRunning() && !events.empty()) {
        hsm.tick();
        cout << "Tick # " << setw(6) << hsm.getGlobalTime() << " State: " << setw(20) << hsm.getCurrentState() << endl;
        if (events.front().time <= hsm.getGlobalTime()) {
           dispatch(m, events.front(), hsm);
           events.pop();
           cout << " Current state: " << hsm._state->stateName << endl;
        }
        else if (hsm.getTimeFlag()) {// if time flag is set, the current state has set a timer. 
            if (hsm.getGlobalTime() - hsm.getTimeStart()  >= hsm.getTimeLimit()) {               cout << " Timeout exception caught in state: " << hsm._state->stateName << " Tick # " << setw(6) << hsm.getGlobalTime();               hsm.TIMEOUT();               cout << "Current state: " << hsm._state->stateName << endl;
            }
        }
    std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    return 0;
}

bool dispatch(state_func_map_t m, Event e, HSM &hsm) {
   
   bool result = true;

   state_func_map_t::iterator x = m.find(e.eventName);

   if (x != m.end()) {
       (hsm.*(x->second))();
       cout << "Dispatched " << setw(20) << e.eventName << " @ "
           << "Tick # " << setw(4) << hsm.getGlobalTime();
   }   else {       std::cout << e.eventName << " not handled. in state " << hsm._state->stateName << std::endl;
       result = false;
   }

   return result;
}
bool parseEventsFromInput(queue<Event> &q, string s) {
   std::ifstream infile(s);
   string en;
   int et;
   Event* e;

   if (!(infile >> en >> et)) {
       cout << " error, could not read first line! Abort." << endl;
       return false;
   }
   e = new Event(en, et);
   q.push(*e);

   while (infile >> en >> et)
   {
       // successfully extracted one line, data is in x1, ..., x4, c.
       e = new Event(en, et);
       q.push(*e);
   }

   return true;

}
