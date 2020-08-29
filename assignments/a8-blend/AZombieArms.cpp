#include "AnimationToolkit.h"
#include "AFramework.h"
#include "ASkeletonDrawer.h"
#include "GL/glew.h"
#include "GL/glut.h"
#include <algorithm>
#include <string>

class AZombieArms : public AFramework
{
public:
   AZombieArms() : AFramework(AFramework::Perspective) {}
   virtual ~AZombieArms() {}

   void setup()
   {
      ABVHReader reader;
      reader.load("../motions/Beta/walking.bvh", _skeleton, _original);

      _zombieFreeze = ComputeArmFreeze(_original);
      _zombieOffset = ComputeArmOffset(_original);
   }

   AMotion ComputeArmOffset(const AMotion& motion)
   {
      AMotion result = motion;

      AMatrix3 lArmRot(AMatrix3::XYZ, AVector3(-53, -88, -33) * ADeg2Rad);
      AMatrix3 rArmRot(AMatrix3::XYZ, AVector3(14, 88, -33)  * ADeg2Rad);
      AMatrix3 farmRot(AMatrix3::XYZ, AVector3(0, 23, 0) * ADeg2Rad);
      AMatrix3 farmRotL(AMatrix3::XYZ, AVector3(0, -23, 0) * ADeg2Rad);

      AJoint* lArm = _skeleton.getByName("Beta:LeftArm");
      AJoint* rArm = _skeleton.getByName("Beta:RightArm");
      AJoint* lFarm = _skeleton.getByName("Beta:LeftForeArm");
      AJoint* rFarm = _skeleton.getByName("Beta:RightForeArm");
      APose pose = result.getKey(0);

      AQuaternion offset = lArmRot.toQuaternion() * pose.jointRots[lArm->getID()].inverse();
      AQuaternion offset1 = rArmRot.toQuaternion() * pose.jointRots[rArm->getID()].inverse();

      for(int x=0; x<result.getNumKeys(); x++)
      {
         //"Beta:LeftArm", "Beta:RightArm" (shoulders), "Beta:LeftForeArm", and "Beta:RightForeArm" (elbows). 
         pose = result.getKey(x);

         pose.jointRots[lArm->getID()] = offset * pose.jointRots[lArm->getID()];
         pose.jointRots[lFarm->getID()] = farmRotL;
         pose.jointRots[rArm->getID()] = offset1 * pose.jointRots[rArm->getID()];
         pose.jointRots[rFarm->getID()] = farmRot;

         result.editKey(x, pose);
      }

      return result;
   }

   AMotion ComputeArmFreeze(const AMotion& motion)
   {
      AMotion result = motion;

      AMatrix3 lArmRot(AMatrix3::XYZ, AVector3(-53, -88, -33) * ADeg2Rad);
      AMatrix3 rArmRot(AMatrix3::XYZ, AVector3(14, 88, -33)  * ADeg2Rad);
      AMatrix3 farmRot(AMatrix3::XYZ, AVector3(0, 23, 0) * ADeg2Rad);
      AMatrix3 farmRotL(AMatrix3::XYZ, AVector3(0, -23, 0) * ADeg2Rad);

      AJoint* lArm = _skeleton.getByName("Beta:LeftArm");
      AJoint* rArm = _skeleton.getByName("Beta:RightArm");
      AJoint* lFarm = _skeleton.getByName("Beta:LeftForeArm");
      AJoint* rFarm = _skeleton.getByName("Beta:RightForeArm");

      for(int x=0; x<result.getNumKeys(); x++)
      {
         //"Beta:LeftArm", "Beta:RightArm" (shoulders), "Beta:LeftForeArm", and "Beta:RightForeArm" (elbows). 
         APose pose = result.getKey(x);

         pose.jointRots[lArm->getID()] = lArmRot;
         pose.jointRots[lFarm->getID()] = farmRotL;
         pose.jointRots[rArm->getID()] = rArmRot;
         pose.jointRots[rFarm->getID()] = farmRot;

         result.editKey(x, pose);
      }

      return result;
   }

   void update()
   {
      double t =  elapsedTime() * 0.5;
      if (_currentMotion == 1) 
      {
         _zombieFreeze.update(_skeleton, t);
      }
      else if (_currentMotion == 2) 
      {
         _zombieOffset.update(_skeleton, t);
      }
      else 
      {
         _original.update(_skeleton, t);
      }
   }

   void draw()
   {  
      _drawer.draw(_skeleton);
   }

   void keyPress(unsigned char key, int specialKey, int x, int y) 
   {
      if (key == '1')
      {
          _currentMotion = 1;
      }
      else if (key == '2')
      {
          _currentMotion = 2;
      }
      else if (key == '0')
      {
          _currentMotion = 0;
      }
   }

   ASkeletonDrawer _drawer;
   ASkeleton _skeleton;
   AMotion _original;
   AMotion _zombieFreeze;
   AMotion _zombieOffset;
   int _currentMotion = 0;
};

int main(int argc, char** argv)
{
   AZombieArms viewer;
   viewer.init(argc, argv);
   viewer.run();
   return 0;
}

