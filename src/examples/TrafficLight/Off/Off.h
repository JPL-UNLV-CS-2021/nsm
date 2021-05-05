#ifndef Off_
#define Off_
#include "../HSMState/HSMState.h"

class Off : public HSMState {
public:
    static HSMState* _self;
    Off();
    virtual void Entry();
    virtual void Exit();

    static HSMState* Instance() {
        return _self;
    }

};

#endif