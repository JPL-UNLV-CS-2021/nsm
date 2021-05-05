#include "../pedestriansEnabled/pedestriansEnabled.h"

class pedestriansWalk : public pedestriansEnabled {
public:
    pedestriansWalk();
    virtual void Entry();
    virtual void Exit();
    virtual void TIMEOUT();
    static HSMState* _self;
    static HSMState* Instance() {

        return _self;
    }

};