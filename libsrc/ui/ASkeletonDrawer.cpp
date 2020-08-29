#include "ASkeletonDrawer.h"
#include "AConstants.h"
#include "AVector3.h"
#include "AGLObjects.h"
#include <GL/glut.h>
#include <algorithm>
#include <iostream>

const AVector3 LIGHT_BLUE(0.459f, 0.729f, 1.0f);
const AVector3 DARK_BLUE(0.0510, 0.1255, 0.4627);
const AVector3 DARK_YELLOW(0.9922, 0.8392, 0.1725);
const AVector3 LIGHT_RED(1.0, 0.5, 0.5);
const AVector3 LIGHT_GREEN(0.0, 1.0, 0.25);

ASkeletonDrawer::ASkeletonDrawer() :
    _color(LIGHT_BLUE),
    _offsetPosition(AVector3::Zero),
    _offsetRotation(AMatrix3::Identity),
    _scale(1.0),
    _axisLength(10.0f),
    _jointRadius(5.0f),
    _drawAxes(false)
{
}

ASkeletonDrawer::~ASkeletonDrawer()
{
}

void ASkeletonDrawer::setColor(const AVector3& c)
{
    _color = c;
}

AVector3 ASkeletonDrawer::getColor() const
{
    return _color;
}


void ASkeletonDrawer::setJointRadius(float r)
{
    _jointRadius = r;
}

float ASkeletonDrawer::getJointRadius() const
{
    return _jointRadius;
}


void ASkeletonDrawer::setAxisLength(float r)
{
    _jointRadius = r;
}

float ASkeletonDrawer::getAxisLength() const
{
    return _axisLength;
}

void ASkeletonDrawer::setShowAxis(bool b)
{
    _drawAxes = b;
}

bool ASkeletonDrawer::getShowAxis() const
{
    return _drawAxes;
}

void ASkeletonDrawer::setOffsetPosition(const AVector3& p)
{
    _offsetPosition = p;
}

AVector3 ASkeletonDrawer::getOffsetPosition() const
{
    return _offsetPosition;
}

void ASkeletonDrawer::setOffsetRotation(const AMatrix3& m)
{
    _offsetRotation = m;
}

AMatrix3 ASkeletonDrawer::getOffsetRotation() const
{
    return _offsetRotation;
}

void ASkeletonDrawer::setScale(float m)
{
    _scale = m;
}

float ASkeletonDrawer::getScale() const
{
    return _scale;
}

void ASkeletonDrawer::draw(const ASkeleton& skeleton)
{
    ASetMaterial(_color);

    glPushMatrix();
    ASetPosition(_offsetPosition);
    ASetRotation(_offsetRotation);
    glScalef(_scale, _scale, _scale);

    if (skeleton.getNumJoints() > 0)
    {
        AJoint* pJoint = skeleton.getRoot();
        drawJoint(pJoint->getLocal2Global());

        int totalChildren = pJoint->getNumChildren();
        for (int i = 0; i < totalChildren; i++)
            drawBodyParts(pJoint->getChildAt(i));
    }
    glPopMatrix();
}

void ASkeletonDrawer::drawBodyParts(AJoint* currentJoint)
{
    ASetMaterial(_color);
    drawJoint(currentJoint->getLocal2Global());    

    AJoint* pParent = currentJoint->getParent();
    ADrawLimb(pParent->getGlobalTranslation(), 
        currentJoint->getGlobalTranslation(), _jointRadius);

    // don't draw hands
    if (currentJoint->getName().find("Hand") != std::string::npos) return; 
   
    int totalChildren = currentJoint->getNumChildren();
    for (int i = 0; i < totalChildren; i++)
        drawBodyParts(currentJoint->getChildAt(i));
}

void ASkeletonDrawer::drawJoint(const ATransform& globalTransform)
{
    const AVector3& globalPosition = globalTransform.translation;
    const AMatrix3& globalRotation = globalTransform.rotation.toMatrix();

    ADrawSphere(globalPosition, _jointRadius);

    if (_drawAxes) // Draw axes
    {
        AVector3 x = globalRotation * _axisLength * AVector3(1,0,0);
        AVector3 y = globalRotation * _axisLength * AVector3(0,1,0);
        AVector3 z = globalRotation * _axisLength * AVector3(0,0,1);

        glDisable(GL_LIGHTING);

        glColor3f(1.0f,0.0f,0.0f);
        ADrawLine(globalPosition, globalPosition + x);

        glColor3f(0.0f,1.0f,0.0f);
        ADrawLine(globalPosition, globalPosition + y);

        glColor3f(0.0f,0.0f,1.0f);
        ADrawLine(globalPosition, globalPosition + z);

        glEnable(GL_LIGHTING);
    }
}
