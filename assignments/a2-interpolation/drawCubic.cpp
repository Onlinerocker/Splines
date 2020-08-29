#include <iostream>
#include <AntTweakBar.h>
#include "AFramework.h"
#include "AGLObjects.h"
#include "Cubic.h"

class DrawCubic : public AFramework
{
public:
    DrawCubic() : AFramework(AFramework::Orthographic)
    {
        _deCasteljau.setB0(AVector3(100,  50, 0));
        _deCasteljau.setB1(AVector3(150, 200, 0));
        _deCasteljau.setB2(AVector3(250, 100, 0));
        _deCasteljau.setB3(AVector3(300, 300, 0));
        _deCasteljau.setColor(AVector3(0,0,1));

        _bernstein.setB0(AVector3(100,  50, 0));
        _bernstein.setB1(AVector3(150, 200, 0));
        _bernstein.setB2(AVector3(250, 100, 0));
        _bernstein.setB3(AVector3(300, 300, 0));
        _bernstein.setColor(AVector3(0,0,1));
        _type = CUBIC_BERNSTEIN;
    }

    void draw()
    {
        if (_type == CUBIC_CASTELJAU)
        {
            _deCasteljau.draw();

            ASetColor(AVector3(0,0,1));
            ADrawSphere(_deCasteljau.b0(), 5);
            ADrawSphere(_deCasteljau.b3(), 5);

            ASetColor(AVector3(1,1,0));
            ADrawSphere(_deCasteljau.b1(), 5);
            ADrawSphere(_deCasteljau.b2(), 5);
        }
        else
        {
            _bernstein.draw();
            ASetColor(AVector3(0,0,1));
            ADrawSphere(_bernstein.b0(), 5);
            ADrawSphere(_bernstein.b3(), 5);

            ASetColor(AVector3(1,1,0));
            ADrawSphere(_bernstein.b1(), 5);
            ADrawSphere(_bernstein.b2(), 5);
        }
        
    }

    void initializeGui()
    {
        TwBar* curveBar = TwNewBar("Curve controls");
        TwDefine(" 'Curve controls' size='200 100' position='5 5' iconified=false fontresizable=false alpha=200");
        TwEnumVal curveTypeEV[] = 
        { 
            { CUBIC_BERNSTEIN, "Berstein-Bezier" },
            { CUBIC_CASTELJAU, "Casteljau-Bezier" }, 
        };
        TwType curveType = TwDefineEnum("Interpolation Type", curveTypeEV, 2);
        TwAddVarRW(curveBar, "Type", curveType, &_type, NULL);
    }

private:
    CubicDeCasteljau _deCasteljau;
    CubicBernstein _bernstein;
    enum InterpolationType 
    { 
        CUBIC_BERNSTEIN, 
        CUBIC_CASTELJAU 
    } _type;
};

int main(int argc, char **argv)
{
    DrawCubic viewer;
    viewer.init(argc, argv, 400, 400);
    viewer.run();
}
