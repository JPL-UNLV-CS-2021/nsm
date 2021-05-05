#include "../vehiclesEnabled/vehiclesEnabled.h"
class vehiclesYellow : public vehiclesEnabled {
public:
    vehiclesYellow();
    virtual void Entry();
    virtual void Exit();
    virtual void TIMEOUT();
    static HSMState* _self;

    static HSMState* Instance() {


        return _self;
    }
};
