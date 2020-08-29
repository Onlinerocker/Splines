#include <iostream>
#include "AFramework.h"
#include "AVector3.h"
#include "AMatrix3.h"
#include "AGLObjects.h"
#include <math.h>

class AField : public AFramework
{
public:
    float* angles;

    AField() : AFramework(AFramework::Orthographic)
    {
    }

    virtual ~AField()
    {
        free(angles);
    }

    virtual void setup()
    {
        angles = new float[400];

        for(int x=0; x<400; x++)
            angles[x] = 0;

        _buttonDown = false;
    }



    virtual void draw()
    {
        AVector3 mousePos = AVector3(_mouseX, _mouseY, 10);
        ASetColor(AVector3(1,0,0));
        ADrawSphere(mousePos, 10);

        int ind = 0;
        for(int x=0; x<500; x+= 25)
        {
            for(int y=0; y<500; y+= 25)
            {
                ASetColor(AVector3(0,1,0));
                AVector3 pos = AVector3(x+12.5,500 - (y+12.5),0); 

                AVector3 relPos = pos - mousePos;

                float theta = atan2(relPos.y(), relPos.x());
                AMatrix3 rotMat = AMatrix3();
                rotMat.fromEulerAnglesXYZ(AVector3(0,0,angles[ind]));

                if(AVector3().Distance(mousePos, pos) <= 100 && _buttonDown){
                    angles[ind] = theta;
                    rotMat.fromEulerAnglesXYZ(AVector3(0,0,theta));
                }
                else if(angles[ind] != 0){
                    float thetaNew = angles[ind] * pow(0.1, dt());
                    angles[ind] = thetaNew;
                    rotMat.fromEulerAnglesXYZ(AVector3(0,0,thetaNew));
                }

                ADrawCube(pos, rotMat, AVector3(25,1,10));
                ind++;
            }
        }
    }

    void mousePress(int button, int state, int x, int y) 
    {
        _buttonDown = !_buttonDown;
    }

    void mouseMove(int x, int y) 
    {
        _mouseX = x;
        _mouseY = getHeight() - y;
    }

private:
    int _mouseX;
    int _mouseY;
    int _buttonDown;
};

int main(int argc, char** argv)
{
    AField viewer;
    viewer.init(argc, argv, 500,500);
    viewer.run();
    return 0;
}
