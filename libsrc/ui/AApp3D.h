#ifndef AApp2D_H_
#define AApp2D_H_

#include "GL/glew.h"
#include "GL/glut.h"
#include "ACamera.h"
#include "AApp.h"
#include <AntTweakBar.h>
#include <vector>

class AApp3D : public AApp
{
public:
    AApp3D(AFramework* framework);
    virtual ~AApp3D();
    virtual ACamera* getCamera();

protected:

    virtual void onAppInitializeView();
    virtual void onAppMouseMotion(int x, int y);
    virtual void onAppMouse(int button, int state, int x, int y);
    virtual void onAppKeyboard(unsigned char key, int x, int y);
    virtual void onAppDraw();

    virtual void draw3DView();
    virtual void drawOverlay();
    virtual void frameCamera(const AVector3& center, const AVector3& dim);
    virtual void displayGrid();

protected:
    ACamera mCamera;
    mutable int mLastX, mLastY;
    int mMenu;
    int mButtonState;
    int mModifierState;
    int mWindowWidth, mWindowHeight;

public:
   static int GridSize;
};

#endif
