#include "AnimationToolkit.h"
#include "AFramework.h"
#include "ACyclops.h"
#include "AGLObjects.h"
#include "GL/glew.h"
#include "GL/glut.h"
#include <algorithm>
#include <string>

class ALooker : public AFramework
{
public:
   ALooker() : AFramework(AFramework::Perspective) {}
   virtual ~ALooker() {}

   void setup()
   {
      AMotion motion;
      ABVHReader reader;
      reader.load("../motions/Beta/idle.bvh", _skeleton, motion);
      motion.update(_skeleton, 0);
      _drawer.setColor(AVector3(1,0,0));
      _head = _skeleton.getByName("Beta:Head");
   }

   void reset(AJoint* head)
   {
      head->setLocalRotation(AQuaternion::Identity);
      head->fk();
   }

   void lookAtTarget(AJoint* head, const AVector3& target)
   {
      // Compute a local rotation for the head so that the 
      // character looks at target using the axis/angle calculation from 
      // the CCD algorithm

      // 1. Compute the rotation axis and angle that points the 
      // forward direction of the head (the Z axis in local coordinates)
      // towards the target (perform this step in global coordinates)

      // 2. Compute and set the local rotation for the head and call fk

      AVector3 dir = AVector3(0,0,1);
      AVector3 error = target - head->getGlobalTranslation();
      AVector3 cross = AVector3::Cross(dir, error);
      AVector3 axis = cross / cross.length();
      double phi = atan2(cross.length(), AVector3::Dot(dir,dir) + AVector3::Dot(dir,error));

      AQuaternion locQuat = head->getLocal2Global().inverse().rotation * AQuaternion(axis,phi);
      head->setLocalRotation(locQuat);
      head->fk();
   }

   void update()
   {
      double r = 100;
      double angle = elapsedTime();
      _target = AVector3(r * cos(angle), r * sin(angle) + r, 150);

      reset(_head);
      lookAtTarget(_head, _target);
   }

   void draw()
   {  
      _drawer.draw(_skeleton);

      AVector3 globalHeadPos = _head->getGlobalTranslation();
      AVector3 globalForward = _head->getGlobalRotation() * AVector3(0,0,1);

      ASetMaterial(AVector3(0,0,1));
      ADrawLine(globalHeadPos, globalHeadPos + 500*globalForward);
      ADrawSphere(_target, 5);
   }

   void keyPress(unsigned char key, int specialKey, int x, int y) 
   {
   }

protected:
   ACyclops _drawer;
   ASkeleton _skeleton;
   AJoint* _head;
   AVector3 _target;
};

int main(int argc, char** argv)
{
   ALooker viewer;
   viewer.init(argc, argv);
   viewer.run();
   return 0;
}

