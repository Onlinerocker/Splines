#include "AnimationToolkit.h"
#include "AFramework.h"
#include "AGLObjects.h"
#include "ATimer.h"
#include <string>
#include <cmath>
#include <algorithm>
#include <iostream>

class ASlerpTeapot : public AFramework
{
public:
    ASlerpTeapot() : AFramework(AFramework::Orthographic) {}
    virtual ~ASlerpTeapot() {}

protected:

    virtual void setup()
    {
       AQuaternion q0, q1, q2;
       q0.fromAxisAngle(AVector3(0, 0, 1),  60 * ADeg2Rad);
       q1.fromAxisAngle(AVector3(0, 0, 1), -200 * ADeg2Rad);
       q2.fromAxisAngle(AVector3(0, 1, 0),  90 * ADeg2Rad);
       mSpline.appendKey(0, q0);
       mSpline.appendKey(3, q1);
       mSpline.appendKey(6, q2);
       mSpline.appendKey(9, q0);

       glEnable(GL_DEPTH_TEST);
       glDepthFunc(GL_LEQUAL);
       glShadeModel(GL_SMOOTH);

       glEnable(GL_NORMALIZE);
       glEnable(GL_COLOR_MATERIAL);
       glColorMaterial(GL_FRONT_AND_BACK, GL_DIFFUSE);
       glDisable(GL_CULL_FACE);

       // Setup lighting
       glEnable(GL_LIGHTING);
       glEnable(GL_LIGHT0);
       float AmbientColor[] = { 0.01f, 0.01f, 0.01f, 1.0f };   glLightfv(GL_LIGHT0, GL_AMBIENT, AmbientColor);
       float DiffuseColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };   glLightfv(GL_LIGHT0, GL_DIFFUSE, DiffuseColor);
       float SpecularColor[] = { 0.0f, 0.0f, 0.0f, 1.0f };   glLightfv(GL_LIGHT0, GL_SPECULAR, SpecularColor); 
       float Position[] = { 1.0f, 1.0f, 4.0f, 1.0f };  glLightfv(GL_LIGHT0, GL_POSITION, Position);

       glClearStencil(0); //clear the stencil buffer
       glClearDepth(1.0f);

       glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
       glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
       glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
       glEnable(GL_LINE_SMOOTH);
       glEnable(GL_POLYGON_SMOOTH);
       glEnable(GL_MULTISAMPLE);
    }

    virtual void update()
    {
       mQ = mSpline.getValue(elapsedTime(), true); 
    }

    virtual void draw()
    {
       glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

       glMatrixMode(GL_PROJECTION);
       glLoadIdentity();
       glOrtho(-3, 3, -3, 3, 0.01, 100);
       glMatrixMode(GL_MODELVIEW);
       glLoadIdentity();
       gluLookAt(0, 0, -10, 0, 0, 0, 0, 1, 0);

       double angle;
       AVector3 axis;
       mQ.toAxisAngle(axis, angle);
       ASetMaterial(AVector3(1, 1, 0));
       glPushMatrix();
       glRotatef(angle * ARad2Deg, axis[0], axis[1], axis[2]);
       glutSolidTeapot(1.25);
       glPopMatrix();
    }

protected:

    AQuaternion mQ;
    AQuatSpline mSpline;
};

int main(int argc, char** argv)
{
   ASlerpTeapot viewer;
   viewer.init(argc, argv);
   viewer.run();
}

