#ifndef ARotationsViewer_H_
#define ARotationsViewer_H_

#include <AntTweakBar.h>
#include "AnimationToolkit.h"
#include "AFramework.h"
#include "ATimer.h"

class ATeapotsViewer : public AFramework
{
public:
    ATeapotsViewer();
    virtual ~ATeapotsViewer();

protected:

    enum RotOrder { XYZ, XZY, YXZ, YZX, ZXY, ZYX } mRotOrder;

    virtual void setup();
    virtual void initializeGui();
    virtual void draw();
    virtual void drawDemo1();
    virtual void pushEulerRotation(RotOrder roo, const AVector3& euler);
    virtual void drawText(int x, int y, const std::string& text);

protected:

    TwBar *mDemoBar;
    TwType rooType;
    double mXAngle, mYAngle, mZAngle;
};

#endif
