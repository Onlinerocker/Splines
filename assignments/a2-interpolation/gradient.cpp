#include <iostream>
#include "AFramework.h"
#include "AGLObjects.h"

class Gradient : public AFramework
{
public:
    Gradient() : AFramework(AFramework::Orthographic)
    {
    }

    virtual void draw()
    {
        for(int x=0; x<440; x+= 40)
        {
            for(int y=0; y<440; y+= 40)
            {
                AVector3 colZero = calcCol(x/400.0, AVector3(1,1,0), AVector3(0,1,1));
                AVector3 colOne = calcCol(x/400.0, AVector3(1,0,0), AVector3(1,0,1));

                ASetColor(calcCol(y/400.0,colZero,colOne));
                ADrawCube(AVector3(x+20,400 - (y+20),0), AMatrix3::Identity, AVector3(40,40,10));
            }
        }
    }

    AVector3 calcCol(float tx, AVector3 col, AVector3 col1)
    {
        AVector3 colNew = (1.0 - tx) * col + tx*col1;
        return colNew;
    }
};

int main(int argc, char **argv)
{
    Gradient viewer;
    viewer.init(argc, argv, 400, 400);
    viewer.run();
}
