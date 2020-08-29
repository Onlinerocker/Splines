#include <iostream>
#include <functional>
#include <random>
#include <list>
#include <AntTweakBar.h>
#include "AFramework.h"
#include "AGLObjects.h"
#include "Cubic.h"

class AnimateCubic : public AFramework
{
public:
    AnimateCubic() : AFramework(AFramework::Orthographic)
    {
    }

    void setup()
    {
        _curve1.setB0(AVector3(getWidth()*0.25, getHeight()*0.50,0));
        _curve1.setB2(AVector3(getWidth()*0.05, getHeight()*0.75, 0));
        _curve1.setB1(AVector3(getWidth()*0.95, getHeight()*0.75, 0));
        _curve1.setB3(AVector3(getWidth()*0.75, getHeight()*0.50,0));
        _curve1.setColor(AVector3(1,1,0));

        _curve2.setB0(AVector3(getWidth()*0.25, getHeight()*0.50,0));
        _curve2.setB1(AVector3(getWidth()*0.35, getHeight()*0.25, 0));
        _curve2.setB2(AVector3(getWidth()*0.65, getHeight()*0.25, 0));
        _curve2.setB3(AVector3(getWidth()*0.75, getHeight()*0.50,0));
        _curve2.setColor(AVector3(1,0,1));

        
        _totalTime = 5.0;
        _timeElap = 0.0;
        _mod = 1;
    }

    AVector3 lerp(AVector3 pos, AVector3 pos1, double t){
        return (1.0 - t) * pos + (t*pos1);
    }

    void update()
    {
        _timeElap += dt() * _mod;

        if(_timeElap > _totalTime){
            _mod *= -1;
            _timeElap = _totalTime;
        }else if(_timeElap < 0){
            _mod *= -1;
            _timeElap = 0;
        }

        _current.setColor(lerp(_curve1.color(), _curve2.color(),_timeElap / _totalTime));
        _current.setB0(lerp(_curve1.b0(), _curve2.b0(),_timeElap / _totalTime));
        _current.setB1(lerp(_curve1.b1(), _curve2.b1(),_timeElap / _totalTime));
        _current.setB2(lerp(_curve1.b2(), _curve2.b2(),_timeElap / _totalTime));
        _current.setB3(lerp(_curve1.b3(), _curve2.b3(),_timeElap / _totalTime));
    }

    void draw()
    {
        _curve1.draw();
        _curve2.draw();
        _current.draw();
    }

private:
    // Note: You could use CubicBernstein here instead
    CubicDeCasteljau _curve1;
    CubicDeCasteljau _curve2;
    CubicDeCasteljau _current;
    float _totalTime;
    float _timeElap;
    float _mod;
};

int main(int argc, char **argv)
{
    AnimateCubic viewer;
    viewer.init(argc, argv, 400, 400);
    viewer.run();
}