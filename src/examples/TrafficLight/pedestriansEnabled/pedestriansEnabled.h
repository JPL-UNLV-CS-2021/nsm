#ifndef pedestriansEnabled_
#define pedestriansEnabled_

#include "../Operational/Operational.h"


class pedestriansEnabled : public Operational {
public:
    pedestriansEnabled();
    virtual void Entry();
    virtual void Exit();
    static HSMState* _self;

    static HSMState* Instance() {

        return _self;
    }



};
#endif