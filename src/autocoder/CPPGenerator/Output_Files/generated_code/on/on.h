#ifndef on_
#define on_
#include "../HSMState/HSMState.h"
class on : public HSMState {
public:
    static HSMState* _self;
    on();
    virtual void Entry();
    virtual void Exit();
    static HSMState* Instance() {
       return _self;
    }
    virtual void TIMEOUT();
    virtual void JUNCTION_EVENT();
};
#endif 