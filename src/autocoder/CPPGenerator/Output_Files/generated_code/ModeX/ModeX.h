#ifndef ModeX_
#define ModeX_
#include "../HSMState/HSMState.h"
class ModeX : public HSMState {
public:
    static HSMState* _self;
    ModeX();
    virtual void Entry();
    virtual void Exit();
    static HSMState* Instance() {
       return _self;
    }
    virtual void TIMEOUT();
};
#endif 