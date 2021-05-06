//
// Created by Michael Fields on 2/21/21.
//



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
