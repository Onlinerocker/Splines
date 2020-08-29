#include <iostream>
#include <AntTweakBar.h>
#include "AFramework.h"
#include "AGLObjects.h"
#include "Cubic.h"

class ParticleCubic : public AFramework
{
public:
    ParticleCubic() : AFramework(AFramework::Orthographic)
    {
        _curve.setB0(AVector3(100,  50, 0));
        _curve.setB1(AVector3(150, 200, 0));
        _curve.setB2(AVector3(250, 100, 0));
        _curve.setB3(AVector3(300, 300, 0));
        _curve.setColor(AVector3(1,1,0));

        _totalTime = 5.0;
        _timeElap = 0.0;
    }

    void draw()
    {
        _curve.draw();
        _timeElap += dt();

        if(_timeElap > _totalTime)
            _timeElap = 0;

        AVector3 pos = _curve.interpolate(_timeElap / _totalTime);
        ASetColor(AVector3(1,0,0));
        ADrawSphere(pos, 4);
    }

private:
    CubicDeCasteljau _curve;
    float _totalTime;
    float _timeElap;
};

int main(int argc, char **argv)
{
    ParticleCubic viewer;
    viewer.init(argc, argv, 400, 400);
    viewer.run();
}
