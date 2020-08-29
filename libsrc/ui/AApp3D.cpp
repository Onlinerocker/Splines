#include <string>
#include "AApp3D.h"
#include "AOsUtils.h"
#include <algorithm>

using namespace std;

int AApp3D::GridSize = 500;

AApp3D::AApp3D(AFramework* framework) :
    AApp(framework)
{
}

AApp3D::~AApp3D()
{
}

void AApp3D::onAppInitializeView()
{
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    float AmbientColor[] = { 0.0, 0.0, 0.0, 0.0f };   
    glLightfv(GL_LIGHT0, GL_AMBIENT, AmbientColor);

    float DiffuseColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };   
    glLightfv(GL_LIGHT0, GL_DIFFUSE, DiffuseColor);

    float SpecularColor[] = { 0.0f, 0.0f, 0.0f, 0.0f };  
    glLightfv(GL_LIGHT0, GL_SPECULAR, SpecularColor);

    float Position[] = { 1.0f, 1.0f, 4.0f, 1.0f };  
    glLightfv(GL_LIGHT0, GL_POSITION, Position);

    AVector3 pos(0, 0, 0);
    AVector3 dim(100, 200., 100);
    frameCamera(pos, dim);
}

void AApp3D::frameCamera(const AVector3& center, const AVector3& extents)
{
    mCamera.frameVolume(center, extents);
}

void AApp3D::onAppMouseMotion(int pX, int pY)
{
    if (mModifierState != 0) return; 
    int deltaX = mLastX - pX;
    int deltaY = mLastY - pY;
    bool moveLeftRight = abs(deltaX) > abs(deltaY);
    bool moveUpDown = !moveLeftRight;
    if (mButtonState == GLUT_LEFT_BUTTON)  // Rotate
    {
    	if (moveLeftRight && deltaX > 0) mCamera.orbitLeft(deltaX);
    	else if (moveLeftRight && deltaX < 0) mCamera.orbitRight(-deltaX);
    	else if (moveUpDown && deltaY > 0) mCamera.orbitUp(deltaY);
    	else if (moveUpDown && deltaY < 0) mCamera.orbitDown(-deltaY);
    }
    else if (mButtonState == GLUT_MIDDLE_BUTTON) // Zoom
    {
    	if (moveUpDown && deltaY > 0) mCamera.moveForward(deltaY);
    	else if (moveUpDown && deltaY < 0) mCamera.moveBack(-deltaY);
    }
    else if (mButtonState == GLUT_RIGHT_BUTTON) // Pan
    {
    	if (moveLeftRight && deltaX > 0) mCamera.moveLeft(deltaX);
    	else if (moveLeftRight && deltaX < 0) mCamera.moveRight(-deltaX);
    	else if (moveUpDown && deltaY > 0) mCamera.moveUp(deltaY);
    	else if (moveUpDown && deltaY < 0) mCamera.moveDown(-deltaY);
    }

    mLastX = pX;
    mLastY = pY;
}

void AApp3D::onAppMouse(int pButton, int pState, int pX, int pY)
{
    mButtonState = pButton;
    mModifierState = glutGetModifiers();
    mLastX = pX;
    mLastY = pY;
}

void AApp3D::onAppKeyboard(unsigned char pKey, int x, int y)
{
    if (pKey == 'f')
    {
    	 frameCamera(AVector3::Zero, AVector3(100,200,100));
    }
}

void AApp3D::onAppDraw()
{
    draw3DView();
    drawOverlay();
}

void AApp3D::drawOverlay()
{
}

void AApp3D::draw3DView()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE); 

    // Set the view to the current camera settings.
    mCamera.draw();

    AVector3 cpos = mCamera.getPosition();
    GLfloat pos[4];
    pos[0] = cpos[0];
    pos[1] = cpos[1];
    pos[2] = cpos[2];
    pos[3] = 1.0;
    glLightfv(GL_LIGHT0, GL_POSITION, pos);

    glDisable(GL_LIGHTING);
    displayGrid();

    glEnable(GL_LIGHTING);
}

void AApp3D::displayGrid()
{
    // Draw a grid 500*500
    if (ACamera::gDfltUp[2] == 1) // Z-UP =>rotate
    {
        glPushMatrix();
        glRotatef(90, 1, 0, 0);
    }
    glColor3f(0.8f, 0.8f, 0.8f);
    glLineWidth(1.0);
    const int hw = GridSize;
    const int step = 100;
    const int bigstep = 500;
    int i;

    // Draw Grid
    for (i = -hw; i <= hw; i += step) {

    	if (i % bigstep == 0) {
    		glLineWidth(2.0);
    	}
    	else {
    		glLineWidth(1.0);
    	}
    	if (i == 0) 
      {
         glColor3f(0.3f, 0.3f, 0.7f);
         glBegin(GL_LINES);
         glVertex3i(i, 0, 0);
         glVertex3i(i, 0, hw);
         glEnd();

         glColor3f(0.7f, 0.3f, 0.3f);
         glBegin(GL_LINES);
         glVertex3i(0, 0, i);
         glVertex3i(hw, 0, i);
         glEnd();

    	   glColor4f(0.6f, 0.6f, 0.6f, 1.0f);
         glBegin(GL_LINES);
         glVertex3i(-hw, 0, i);
         glVertex3i(0, 0, i);
         glVertex3i(i, 0, -hw);
         glVertex3i(i, 0, 0);
         glEnd();
      }
      else
      {
         glColor4f(0.6f, 0.6f, 0.6f, 1.0f);
         glBegin(GL_LINES);
         glVertex3i(i, 0, -hw);
         glVertex3i(i, 0, hw);
         glVertex3i(-hw, 0, i);
         glVertex3i(hw, 0, i);
         glEnd();
      }
    }
    if (ACamera::gDfltUp[2] == 1) // Z-UP =>rotate
    {
        glPopMatrix();
    }
}

ACamera* AApp3D::getCamera() 
{
    return &mCamera;
}
