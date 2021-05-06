/**
 * Represents an event that is dispatched to the current state
 */

#ifndef QSM_EVENT_H
#define QSM_EVENT_H

#include <string>

using namespace std;

class Event {
    public:
        Event(string name, string type);
        Event(string name, string type, long timing);
        string Name;
        string Type;
        long Timing;
    private:
        bool executed;
};

#endif //QSM_EVENT_H
