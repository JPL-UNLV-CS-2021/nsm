#ifndef Operational_
#define Operational_
#include <iostream>
#include "../Visitor/Visitor.h"
#include "../Global.h"
#include "State.h"

using namespace std;

namespace QSM {
    class Operational : public State {
    public:
        void Transition(TransitionTypes t, ActualVisitor* tr) const override {
            switch (t) {
            case DEFAULT:
                tr->VisitOperational(this);
                break;
            };
        }
        string SomeMethod() const {
            return "Operational State (Some Method)";
        }
    };
}
#endif