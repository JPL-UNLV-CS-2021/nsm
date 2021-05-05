#ifndef Active_
#define Active_
#include "../HSMState/HSMState.h"
class Active : public HSMState {
public:
    static HSMState* _self;
    Active();
    virtual void Entry();
    virtual void Exit();
    static HSMState* Instance() {
       return _self;
    }
    virtual void TIMEOUT();
};
#endif 