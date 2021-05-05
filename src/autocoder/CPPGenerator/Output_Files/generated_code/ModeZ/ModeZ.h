#ifndef ModeZ_
#define ModeZ_
#include "../ModeY/ModeY.h"

class ModeZ : public ModeY {
public:
    static HSMState* _self;
    ModeZ();
    virtual void Entry();
    virtual void Exit();
    static HSMState* Instance() {
       return _self;
    }
    virtual void LOOP_EVENT();
};
#endif 