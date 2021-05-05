#ifndef EVENT_
#define EVENT_
#include<string>

class Event {


    public:

        std::string eventName = "";
        int time = 0;

        Event(std::string en, int t){
            eventName = en;
            time = t;
        };

};

#endif 