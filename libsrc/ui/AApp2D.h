#ifndef AApp3D_H_
#define AApp3D_H_

#include "GL/glew.h"
#include "GL/glut.h"
#include "ACamera.h"
#include "AApp.h"
#include <AntTweakBar.h>
#include <vector>

class AApp2D : public AApp
{
public:
    AApp2D(AFramework* framework);
    virtual ~AApp2D();

protected:
    virtual void onAppInitializeView();
    virtual void onAppDraw();
};

#endif
