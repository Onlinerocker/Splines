#include <iostream>
#include "AFramework.h"
#include "AGLObjects.h"
#include "AnimationToolkit.h"

class AButterfly : public AFramework
{
public:
   AButterfly() : AFramework(AFramework::Perspective)
   {
   }

   void setup()
   {
      AJoint* body = new AJoint("Body");
      body->setLocalTranslation(AVector3(1,2,1)*100);
      body->setLocalRotation(AQuaternion(AVector3(0,1,0), 45 * ADeg2Rad));
      skeleton.addJoint(body);
      
      AJoint* lwing = new AJoint("LWing");
      lwing->setLocalTranslation(AVector3(0.1,0,0)*100);
      skeleton.addJoint(lwing);

      AJoint* rwing = new AJoint("RWing");
      rwing->setLocalTranslation(AVector3(-0.1,0,0)*100);
      skeleton.addJoint(rwing);

      _trav = 0;
      _mod = 1;
   }

   void update()
   {
      AJoint* body = skeleton.getByName("Body");
      float toTrav = 50 * dt();
      _trav += toTrav;
      body->setLocalTranslation(body->getLocalTranslation() + _mod * AVector3(0,toTrav,0));

      if(_trav >= 50)
      {
         _mod *= -1;
         _trav = 0;
      }

      AJoint* lwing = skeleton.getByName("LWing");
      lwing->setLocalRotation(AQuaternion(AVector3(0,0,1), sin(elapsedTime())));

      AJoint* rwing = skeleton.getByName("RWing");
      rwing->setLocalRotation(AQuaternion(AVector3(0,0,1), -sin(elapsedTime())));
   }

   void draw()
   {
      // Example: Compute global transforms to draw
      // NOTE: We normally call ASkeleton::fk() to compute global transforms!
      AJoint* body = skeleton.getByName("Body");
      ATransform bodyLocal = body->getLocal2Parent();
      ATransform bodyGlobal = bodyLocal; // because body is the root

      // Draw body
      AVector3 e1Local(0,0,100);
      AVector3 e2Local(0,0,-100);
      AVector3 e1Global = bodyGlobal.transformPoint(e1Local);
      AVector3 e2Global = bodyGlobal.transformPoint(e2Local);

      AVector3 greenCol = AVector3(21.0, 93.0, 26.0) *= (1.0/255.0);
      ASetMaterial(greenCol);
      ADrawLimb(e1Global, e2Global, 6);

      // Draw body coordinate axes
      /*AVector3 fwdLocal(0,0,1);
      AVector3 upLocal(0,1,0);
      AVector3 leftLocal(1,0,0);
      AVector3 pGlobal = bodyGlobal.transformPoint(AVector3(0,0,0));
      AVector3 fwdGlobal = bodyGlobal.transformVector(fwdLocal); 
      AVector3 upGlobal = bodyGlobal.transformVector(upLocal); 
      AVector3 leftGlobal = bodyGlobal.transformVector(leftLocal); 

      ASetMaterial(AVector3(0,0,1));
      ADrawLimb(pGlobal, pGlobal + fwdGlobal * 150, 2);
      ASetMaterial(AVector3(0,1,0));
      ADrawLimb(pGlobal, pGlobal + upGlobal * 150, 2);
      ASetMaterial(AVector3(1,0,0));
      ADrawLimb(pGlobal, pGlobal + leftGlobal * 150, 2);*/

      // Draw wings
      AVector3 redCol = AVector3(186, 0, 24) *= (1.0/255.0);
      AVector3 goldCol = AVector3(205, 152, 3) *= (1.0/255.0);

      AJoint* lwing = skeleton.getByName("LWing");
      ATransform lwingGlobal = bodyGlobal * lwing->getLocal2Parent();

      ATransform moveDown = ATransform(AQuaternion::Identity, AVector3(-20, 0, -40));
      ATransform lwingGlobal1 = bodyGlobal * lwing->getLocal2Parent() * moveDown;

      ATransform lwingGeometry(AQuaternion::Identity, AVector3(50,0,0));
      ATransform lwingGeometry1(AQuaternion::Identity, AVector3(50,0,0));
      
      ASetMaterial(redCol);
      ADrawEllipse(lwingGlobal * lwingGeometry, AVector3(60,5,40));
      ASetMaterial(goldCol);
      ADrawEllipse(lwingGlobal1 * lwingGeometry1, AVector3(40,5,40));

      AJoint* rwing = skeleton.getByName("RWing");
      ATransform rwingGlobal = bodyGlobal * rwing->getLocal2Parent();
      
      ATransform moveDown1 = ATransform(AQuaternion::Identity, AVector3(20, 0, -40));
      ATransform rwingGlobal1 = bodyGlobal * rwing->getLocal2Parent() * moveDown1;

      ATransform rwingGeometry(AQuaternion::Identity, AVector3(-50,0,0));
      ATransform rwingGeometry1(AQuaternion::Identity, AVector3(-50,0,0));

      ASetMaterial(redCol); 
      ADrawEllipse(rwingGlobal * rwingGeometry, AVector3(60,5,40));
      ASetMaterial(goldCol);
      ADrawEllipse(rwingGlobal1 * rwingGeometry1, AVector3(40,5,40));
   }

private:
   ASkeleton skeleton;
   float _trav;
   float _mod;
};


int main(int argc, char** argv)
{
   AButterfly viewer;
   viewer.init(argc, argv);
   viewer.run();
}

