#ifndef Trigger_
#define Trigger_
#include <iostream>
#include "../Global.h"
#include "../State/State.h"

namespace QSM {
    using namespace std;
    /*
        Declare base class "Event" for others to inherit from
    */
    class Trigger {
    public:
        virtual ~Trigger() {}
        virtual void VisitOperational(const State* state) const = 0;
    };
}
#endif