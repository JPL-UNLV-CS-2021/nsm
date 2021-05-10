#ifndef TransitionTypes_
#define TransitionTypes_

namespace QSM {
    enum TransitionTypes {
        INITIAL,
        DEFAULT,
        TIMEOUT
    };

    class Operational;
    class ActualVisitor;
}
#endif