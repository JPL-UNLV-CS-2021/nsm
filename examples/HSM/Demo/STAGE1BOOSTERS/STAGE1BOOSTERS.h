#ifndef STAGE1BOOSTERS_
#define STAGE1BOOSTERS_
#include "../HSMState/HSMState.h"
class STAGE1BOOSTERS : public HSMState {
public:
    static HSMState* _self;
    STAGE1BOOSTERS();
    virtual void Entry();
    virtual void Exit();
    static HSMState* Instance() {
       return _self;
    }
    virtual void TIMEOUT();
};
#endif 