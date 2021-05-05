#include "../pedestriansEnabled/pedestriansEnabled.h"
class pedestriansFlash : public pedestriansEnabled {
public:
    pedestriansFlash();
    virtual void Entry();
    virtual void DynamicEntry();
    virtual void Exit();
    virtual void TIMEOUT();
    static HSMState* _self;

    static HSMState* Instance() {

        return _self;
    }

};

