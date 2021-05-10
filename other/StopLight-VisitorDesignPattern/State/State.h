#ifndef State_
#define State_
#include <iostream>
#include "../Global.h"
using namespace std;

namespace QSM {
    /*
        Declare base class "State" for others to inherit from
    */
    class State {
    public:
        virtual ~State() {}
        virtual void Transition(TransitionTypes t, ActualVisitor* tr) const = 0;
        virtual string SomeMethod() const = 0;
    };
}
#endif