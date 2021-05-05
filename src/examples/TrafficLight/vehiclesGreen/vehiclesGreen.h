#include "../vehiclesEnabled/vehiclesEnabled.h"
class vehiclesGreen : public vehiclesEnabled {
public:
    vehiclesGreen();
    virtual void Entry();
    virtual void Exit();

    virtual void PEDESTRIAN_WAITING();
    virtual void TIMEOUT();
    static HSMState* _self;

    static HSMState* Instance() {

        return _self;
    }



};
