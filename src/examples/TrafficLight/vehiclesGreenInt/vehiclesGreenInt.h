#include "../vehiclesEnabled/vehiclesEnabled.h"
class vehiclesGreenInt : public vehiclesEnabled {
public:
    vehiclesGreenInt();
    virtual void Entry();
    virtual void Exit();

    virtual void PEDESTRIAN_WAITING();
    static HSMState* _self;

    static HSMState* Instance() {

        return _self;
    }
};