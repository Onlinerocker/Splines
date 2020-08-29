#include "ACyclops.h"
#include "AGLObjects.h"

ACyclops::ACyclops() :
   ASkeletonDrawer()
{
}

ACyclops::~ACyclops()
{
}

void ACyclops::draw(const ASkeleton& skeleton)
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

        for (int i = 1; i < skeleton.getNumJoints(); i++)
        {
            pJoint = skeleton.getByID(i);
            if (pJoint->getParent()->getName().find("Hand") 
               != std::string::npos) continue; 
            drawBodyParts(pJoint);
        }
    }
    glPopMatrix();
}

void ACyclops::drawBodyParts(AJoint* currentJoint)
{
    if (currentJoint->getName().find("HeadSite") != std::string::npos) 
    {
        // draw eye
        AJoint* pParent = currentJoint->getParent();
        ATransform xform = pParent->getLocal2Global();

        ASetMaterial(AVector3(1,1,1)); 
        AVector3 eyeSize(_jointRadius, _jointRadius, _jointRadius);
        AVector3 eyePos(0, 12, _jointRadius*0.5);
        ADrawEllipse(xform.transformPoint(eyePos), eyeSize);

        // draw pupils in local coordinates
        ASetMaterial(AVector3(0,0,0));
        AVector3 pupilSize = 0.5 * eyeSize;
        AVector3 pupilPos(0, 12, _jointRadius*1.2);
        ADrawEllipse(xform.transformPoint(pupilPos), pupilSize);
    }

    if (currentJoint->getName().find("Beta:Head") != std::string::npos) 
    {
        _drawAxes = true;
        ASetMaterial(_color);
        drawJoint(currentJoint->getLocal2Global());    
        _drawAxes = false;
    }
    else
    {
       ASetMaterial(_color);
       drawJoint(currentJoint->getLocal2Global());    
    }

    AJoint* pParent = currentJoint->getParent();
    ADrawLimb(pParent->getGlobalTranslation(), 
        currentJoint->getGlobalTranslation(), _jointRadius);
}

