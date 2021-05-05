#ifndef Operational_
#define Operational_
#include "../HSMState/HSMState.h"
class Operational : public HSMState {
public:
    Operational();
    virtual void Entry();
    virtual void Exit();
    virtual void OFF();
    static HSMState* _self;
    static HSMState* Instance() {
        return _self;
    }



};
#endif