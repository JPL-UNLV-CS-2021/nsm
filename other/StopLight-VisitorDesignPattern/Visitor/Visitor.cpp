#ifndef ActualVisitor_
#define ActualVisitor_
#include <iostream>
#include "../Global.h"
#include "Visitor.h"
#include "../State/State.h"

namespace QSM {
    class ActualVisitor : public Trigger {
    public:
        void VisitOperational(const State* state) const override {
            cout << state->SomeMethod() << " + ActualVisitor\n";
        }
    };
}
#endif