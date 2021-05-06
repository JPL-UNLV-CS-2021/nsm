#ifndef Scanning_
#define Scanning_
#include "../HSMState/HSMState.h"
class Scanning : public HSMState {
public:
    static HSMState* _self;
    Scanning();
    virtual void Entry();
    virtual void Exit();
    static HSMState* Instance() {
       return _self;
    }
    virtual void TIMEOUT();
    virtual void JUNCTION_EVENT();
};
#endif 