#ifndef vehiclesEnabled_
#define vehiclesEnabled_
#include "../Operational/Operational.h"
class vehiclesEnabled : public Operational {
public:
    vehiclesEnabled();
    virtual void Entry();
    virtual void Exit(); 
    static HSMState* _self;

    static HSMState* Instance() {

        return _self;
    }

};
#endif
