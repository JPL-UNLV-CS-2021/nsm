#include "Event.h"

using namespace std;

Event::Event(string name, string type ) {
    this->Type = type;
    this->Name = name;
    this->Timing = 0;
    this->executed = false;
}

Event::Event(string name, string type, long timing)  {
    this->Type = type;
    this->Name = name;
    this->Timing = timing;
    this->executed = false;
}