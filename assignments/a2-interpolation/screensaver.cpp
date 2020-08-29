#include <iostream>
#include <functional>
#include <random>
#include <list>
#include "AFramework.h"
#include "AGLObjects.h"
#include "Cubic.h"

class Screensaver : public AFramework
{
public:
    Screensaver() : AFramework(AFramework::Orthographic) 
    {
    }
    
    AVector3 lerp(AVector3 pos, AVector3 pos1, double t){
        return (1.0 - t) * pos + (t*pos1);
    }

    AVector3 newRandomPoint(){
        float x = rand() % getWidth(); 
        float y = rand() % getHeight();

        return AVector3(x,y,0); 
    }

    AVector3 newRandomColor(){
        float r = (rand() % 100) / 100.0;
        float g = (rand() % 100) / 100.0;
        float b = (rand() % 100) / 100.0;

        return AVector3(r,g,b);
    }

    void generateNewCurve2(){
        _curve2.setB0(newRandomPoint());
        _curve2.setB1(newRandomPoint());
        _curve2.setB2(newRandomPoint());
        _curve2.setB3(newRandomPoint());
        _curve2.setColor(newRandomColor());
    }

    void setup()
    {
        _trails = new CubicDeCasteljau[50];
        srand(time(NULL));

        _curve1.setB0(AVector3(getWidth()*0.25, getHeight()*0.50,0));
        _curve1.setB2(AVector3(getWidth()*0.05, getHeight()*0.75, 0));
        _curve1.setB1(AVector3(getWidth()*0.95, getHeight()*0.75, 0));
        _curve1.setB3(AVector3(getWidth()*0.75, getHeight()*0.50,0));
        _curve1.setColor(AVector3(1,1,0));

        generateNewCurve2();

        _totalTime = 2.0;
        _timeElap = 0.0;
        _trailInd = 0;
        _trailSize = 0;
    }

    void update()
    {
        _timeElap += dt();
        _timeElap1 += dt();

        if(_timeElap1 >= 0.1){
            //save to array
            _trails[_trailInd] = _current;
            _trailInd++;
            _trailSize++;

            if(_trailInd >= 50){
                _trailInd = 0;
            }

            if(_trailSize > 50){
                _trailSize = 50;
            }
            
            _timeElap1 = 0;
        }

        if(_timeElap >= _totalTime){
            _timeElap = 0;
            _curve1 = _curve2;
            _current = _curve2;
            generateNewCurve2();
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

        for(int x = 0; x < _trailSize; x++){
            _trails[x].draw();
        }
    }

private:
    CubicDeCasteljau _curve1;
    CubicDeCasteljau _curve2;
    CubicDeCasteljau _current;
    CubicDeCasteljau *_trails;

    float _timeElap;
    float _timeElap1;
    float _totalTime;

    int _trailInd;
    int _trailSize;
};

int main(int argc, char** argv)
{
    Screensaver viewer;
    viewer.init(argc, argv, 600, 400);
    viewer.run();
}
