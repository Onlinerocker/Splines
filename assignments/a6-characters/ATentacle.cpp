#include "AFramework.h"
#include "AGLObjects.h"
#include "AnimationToolkit.h"
#include  <math.h>

class ATentacle : public AFramework
{
public:
   ATentacle() : AFramework(AFramework::Perspective) {}
   virtual ~ATentacle() {}
   virtual void setup()
   {
      AJoint* root  = new AJoint("root");
      root->setLocalTranslation(AVector3(0,0,0));
      _tentacle.addJoint(root);

      AJoint* joint1  = new AJoint("joint1");
      joint1->setLocalTranslation(AVector3(0,50,0));
      _tentacle.addJoint(joint1, root);

      AJoint* joint2  = new AJoint("joint2");
      joint2->setLocalTranslation(AVector3(0,50,0));
      _tentacle.addJoint(joint2, joint1);

      AJoint* joint3  = new AJoint("joint3");
      joint3->setLocalTranslation(AVector3(0,50,0));
      _tentacle.addJoint(joint3, joint2);

      AJoint* joint4  = new AJoint("joint4");
      joint4->setLocalTranslation(AVector3(0,50,0));
      _tentacle.addJoint(joint4, joint3);

      _tentacle.fk(); // computes global transforms
   }

   virtual void update()
   {
      // todo animate joints
      AQuaternion quat(AVector3(0,0,1), 45 * ADeg2Rad);

      for(int x=0; x<_tentacle.getNumJoints(); x++)
      {
         _tentacle.getByID(x)->setLocalRotation(AQuaternion(AVector3(0,0,1), sin(elapsedTime() - (x)) ));
      }

      _tentacle.fk(); // computes global transforms
   }

   virtual void draw()
   {
      ASetMaterial(AVector3(0,1,0));
      for (int i = 0; i < _tentacle.getNumJoints(); i++)
      {
         AJoint* joint = _tentacle.getByID(i);
         if (joint->getParent() == NULL) continue;
         
         AVector3 globalParentPos = joint->getParent()->getGlobalTranslation();
         AVector3 globalPos = joint->getGlobalTranslation();
         ADrawLimb(globalParentPos, globalPos, 5);
      }
   }

protected:
   ASkeleton _tentacle;
};

int main(int argc, char** argv)
{
   ATentacle viewer;
   viewer.init(argc, argv);
   viewer.run();
} 

