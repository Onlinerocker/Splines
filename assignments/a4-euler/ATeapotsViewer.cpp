#include "ATeapotsViewer.h"
#include "AConstants.h"
#include "ACamera.h"
#include <string>
#include <algorithm>
#include <iostream>

ATeapotsViewer::ATeapotsViewer() : 
   AFramework(AFramework::Orthographic), 
	mRotOrder(XYZ),
	mXAngle(50), mYAngle(0), mZAngle(0) 
{
}

ATeapotsViewer::~ATeapotsViewer()
{
}

void ATeapotsViewer::draw()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(-5, 5, -5, 5, 0.01, 100);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    gluLookAt(0, 0, -10, 0, 0, 0, 0, 1, 0);

    drawDemo1();
    glPopMatrix();
    glPopMatrix();
  
    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, getWidth(), 0, getHeight());
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glColor3f(1,1,1);
    drawText(getWidth()*0.675, getHeight()*0.675-50, "Euler to Matrix"); // top, right
    drawText(getWidth()*0.5, getHeight()*0.675-50, "YXZ"); // top, middle
    drawText(getWidth()*0.325, getHeight()*0.675-50, "ZYX"); // top, left

    drawText(getWidth()*0.675, getHeight()*0.5-50, "XYZ"); // middle, right
    drawText(getWidth()*0.5, getHeight()*0.5-50, "YZX"); // center
    drawText(getWidth()*0.325, getHeight()*0.5-50, "Quat"); // middle, left

    drawText(getWidth()*0.675, getHeight()*0.325-50, "XZY"); // middle, right
    drawText(getWidth()*0.5, getHeight()*0.325-50, "ZXY"); // center
    drawText(getWidth()*0.325, getHeight()*0.325-50, "Quat to Matrix"); // middle, left
    glPopMatrix();
    glPopMatrix();
    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);
}

void ATeapotsViewer::drawText(int x, int y, const std::string& text)
{
    int stringWidth = 8 * text.size();
    int stringHeight = 13;
    glRasterPos2f(x-stringWidth*0.5, y-stringHeight*0.5);
    for (unsigned int i = 0; i < text.size(); i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13, text[i]);
    }
}

void ATeapotsViewer::pushEulerRotation(
    ATeapotsViewer::RotOrder roo, const AVector3& euler)
{
    switch (roo)
    {
    case XYZ: 
        glRotatef(euler[0], 1, 0, 0);
        glRotatef(euler[1], 0, 1, 0);
        glRotatef(euler[2], 0, 0, 1);
        break;
    case XZY: 
        glRotatef(euler[0], 1, 0, 0);
        glRotatef(euler[2], 0, 0, 1);
        glRotatef(euler[1], 0, 1, 0);
        break;
    case YXZ: 
        glRotatef(euler[1], 0, 1, 0);
        glRotatef(euler[0], 1, 0, 0);
        glRotatef(euler[2], 0, 0, 1);
        break;
    case YZX: 
        glRotatef(euler[1], 0, 1, 0);
        glRotatef(euler[2], 0, 0, 1);
        glRotatef(euler[0], 1, 0, 0);
        break;
    case ZXY: 
        glRotatef(euler[2], 0, 0, 1);
        glRotatef(euler[0], 1, 0, 0);
        glRotatef(euler[1], 0, 1, 0);
        break;
    case ZYX: 
        glRotatef(euler[2], 0, 0, 1);
        glRotatef(euler[1], 0, 1, 0);
        glRotatef(euler[0], 1, 0, 0);
        break;
    }
}

void ATeapotsViewer::drawDemo1()
{
    // test euler to matrix
    AMatrix3 rot;
    AVector3 euler(mXAngle, mYAngle, mZAngle);
    switch (mRotOrder)
    {
    case XYZ: rot.fromEulerAnglesXYZ(euler*ADeg2Rad); break;
    case XZY: rot.fromEulerAnglesXZY(euler*ADeg2Rad); break;
    case YXZ: rot.fromEulerAnglesYXZ(euler*ADeg2Rad); break;
    case YZX: rot.fromEulerAnglesYZX(euler*ADeg2Rad); break;
    case ZXY: rot.fromEulerAnglesZXY(euler*ADeg2Rad); break;
    case ZYX: rot.fromEulerAnglesZYX(euler*ADeg2Rad); break;
    }

    GLfloat glm[16];
    rot.writeToGLMatrix(glm);
    AVector3 testXYZ, testXZY, testYXZ, testYZX, testZXY, testZYX;

    testXYZ = rot.toEulerAnglesXYZ();
    testXZY = rot.toEulerAnglesXZY();
    testYXZ = rot.toEulerAnglesYXZ();
    testYZX = rot.toEulerAnglesYZX();
    testZXY = rot.toEulerAnglesZXY();
    testZYX = rot.toEulerAnglesZYX();

    testXYZ = testXYZ * ARad2Deg;
    testXZY = testXZY * ARad2Deg;
    testYXZ = testYXZ * ARad2Deg;
    testYZX = testYZX * ARad2Deg;
    testZXY = testZXY * ARad2Deg;
    testZYX = testZYX * ARad2Deg;

    AQuaternion quat;
    quat.fromMatrix(rot);
    AVector3 axis; double angle;
    quat.toAxisAngle(axis, angle);
    angle = angle * ARad2Deg;

    AMatrix3 qmat = quat.toMatrix();
    GLfloat qglm[16];
    qmat.writeToGLMatrix(qglm);

    // EXAMPLE: Euler angles mRotOrder
    glColor3f(1, 0, 0);
    glPushMatrix();
    glTranslatef(-3, 3, 0);
    pushEulerRotation(mRotOrder, euler);
    glutSolidTeapot(0.5);
    glPopMatrix();

    // TEST CONVERTING EULER mRotOrder to Matrix
    glColor3f(1, 0.5, 1);
    glPushMatrix();
    glTranslatef(-1.75, 1.75, 0);
    glMultMatrixf(glm);
    glutSolidTeapot(0.5);
    glPopMatrix();
    
    // TEST CONVERTING matrix to EULER XYZ
    glColor3f(0, 0.5, 1);
    glPushMatrix();
    glTranslatef(-1.75, 0, 0);
    pushEulerRotation(XYZ, testXYZ);
    glutSolidTeapot(0.5);
    glPopMatrix();

    // TEST CONVERTING matrix to EULER XZY
    glPushMatrix();
    glTranslatef(-1.75, -1.75, 0);
    pushEulerRotation(XZY, testXZY);
    glutSolidTeapot(0.5);
    glPopMatrix();

    // TEST CONVERTING matrix to EULER YXZ
    glPushMatrix();
    glTranslatef(0, 1.75, 0);
    pushEulerRotation(YXZ, testYXZ);
    glutSolidTeapot(0.5);
    glPopMatrix();

    // TEST CONVERTING matrix to EULER YZX
    glPushMatrix();
    glTranslatef(0, 0, 0);
    pushEulerRotation(YZX, testYZX);
    glutSolidTeapot(0.5);
    glPopMatrix();

    // TEST CONVERTING matrix to EULER ZXY
    glPushMatrix();
    glTranslatef(0, -1.75, 0);
    pushEulerRotation(ZXY, testZXY);
    glutSolidTeapot(0.5);
    glPopMatrix();

    // TEST CONVERTING matrix to EULER ZYX
    glPushMatrix();
    glTranslatef(1.75, 1.75, 0);
    pushEulerRotation(ZYX, testZYX);
    glutSolidTeapot(0.5);
    glPopMatrix();

    // TEST CONVERTING matrix to quaternion to angle/axis
    glColor3f(0.5, 1, 0.5);
    glPushMatrix();
    glTranslatef(1.75, 0, 0);
    glRotatef(angle, axis[0], axis[1], axis[2]);
    glutSolidTeapot(0.5);
    glPopMatrix();
    
    // TEST CONVERTING quaternion to matrix
    glPushMatrix();
    glTranslatef(1.75, -1.75, 0);
    glMultMatrixf(qglm);
    glutSolidTeapot(0.5);
    glPopMatrix();

}

void ATeapotsViewer::setup()
{
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

void ATeapotsViewer::initializeGui()
{
    mDemoBar = TwNewBar("Demo controls");
    TwDefine(" 'Demo controls' size='200 125' position='5 5' iconified=false fontresizable=false alpha=200");

    TwAddVarRW(mDemoBar, "X Angle", TW_TYPE_DOUBLE, &mXAngle, " group='Convert params' ");
    TwAddVarRW(mDemoBar, "Y Angle", TW_TYPE_DOUBLE, &mYAngle, " group='Convert params' ");
    TwAddVarRW(mDemoBar, "Z Angle", TW_TYPE_DOUBLE, &mZAngle, " group='Convert params' ");
    TwEnumVal rooTypeEV[] = { { XYZ, "XYZ" }, { XZY, "XZY" }, { YXZ, "YXZ" }, { YZX, "YZX" }, { ZXY, "ZXY" }, { ZYX, "ZYX" } };
    rooType = TwDefineEnum("RooType", rooTypeEV, 6);
    TwAddVarRW(mDemoBar, "Rot Order", rooType, &mRotOrder, " group='Convert params' ");
}
