#ifndef Thriller_H_
#define Thriller_H_

#include "AGLObjects.h"
#include "ASkeletonDrawer.h"

class ADevil : public ASkeletonDrawer
{
public:
	ADevil()
   {
      _jointRadius = 8;
      setShowAxis(true);
   }

	virtual ~ADevil()
   {
   }

   void drawBodyParts(AJoint* currentJoint)
   {
      ASkeletonDrawer::drawBodyParts(currentJoint);
       // draw eyes
       if (currentJoint->getName() == "HeadTop_End")
       {
           // Use joint's global position and rotation to convert 
           // from local head coordinates to global coordinates
           AJoint* pParent = currentJoint->getParent();
           ATransform xform = pParent->getLocal2Global();

           double headLength = AVector3::Distance(
              pParent->getGlobalTranslation(), 
              currentJoint->getGlobalTranslation());

           // eyes
           double pupilSize = _jointRadius * 0.15;
           ASetMaterial(AVector3(0,0,0));

           AVector3 pupilPosL(_jointRadius*0.3, headLength * 0.75, _jointRadius);
           ADrawSphere(xform.transformPoint(pupilPosL), pupilSize);

           AVector3 pupilPosR(-_jointRadius*0.3, headLength * 0.75, _jointRadius);
           ADrawSphere(xform.transformPoint(pupilPosR), pupilSize);

           // horns
           ASetMaterial(_color);
           double hs = _jointRadius*0.5;
           AVector3 hornPosL(_jointRadius*0.25, headLength, 0);
           AMatrix3 hornRotL(AMatrix3::ZYX, AVector3(-90, 0, -10)*ADeg2Rad);
           ADrawCone(xform*ATransform(hornRotL, hornPosL), AVector3(hs,hs,5*hs));

           AVector3 hornPosR(-_jointRadius*0.5, headLength, 0);
           AMatrix3 hornRotR(AMatrix3::ZYX, AVector3(-90, 0, 10)*ADeg2Rad);
           ADrawCone(xform*ATransform(hornRotR, hornPosR), AVector3(hs,hs,5*hs));
       }
       if (currentJoint->getName() == "RightHand")
       {
           ATransform xform = currentJoint->getLocal2Global();

           double hs = _jointRadius*0.25;
           double len = 100;
           ASetMaterial(AVector3(0,0,0));
           AVector3 spearPos(0, 0, -len*0.5);
           AMatrix3 spearRot(AMatrix3::ZYX, AVector3(0, 0, 0)*ADeg2Rad);
           ADrawCylinder(xform*ATransform(spearRot, spearPos), AVector3(hs,hs,len));

           AVector3 tipPos(0, 0, -len*0.5);
           AMatrix3 tipRot(AMatrix3::ZYX, AVector3(180, 0, 0)*ADeg2Rad);
           ADrawCone(xform*ATransform(tipRot, tipPos), 4*AVector3(hs,hs,hs*2));
       }
   }
};

#endif
