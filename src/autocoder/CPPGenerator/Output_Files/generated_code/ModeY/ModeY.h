#ifndef ModeY_
#define ModeY_
#include "../ModeX/ModeX.h"

class ModeY : public ModeX {
public:
    static HSMState* _self;
    ModeY();
    virtual void Entry();
    virtual void Exit();
    static HSMState* Instance() {
       return _self;
    }
};
#endif 