#ifndef off_
#define off_
#include "../HSMState/HSMState.h"
class off : public HSMState {
public:
    static HSMState* _self;
    off();
    virtual void Entry();
    virtual void Exit();
    static HSMState* Instance() {
       return _self;
    }
    virtual void TIMEOUT();
};
#endif 