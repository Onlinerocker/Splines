#include "AnimationToolkit.h"
#include "AFramework.h"
#include "ACyclops.h"
#include "AGLObjects.h"
#include "GL/glew.h"
#include "GL/glut.h"
#include <algorithm>
#include <string>

class ADancer : public AFramework
{
public:
   ADancer() : AFramework(AFramework::Perspective) {}
   virtual ~ADancer() {}

   void setup()
   {
      ABVHReader reader;
      reader.load("../motions/Beta/idle.bvh", _skeleton, _motion);
      _drawer.setColor(AVector3(1,0,0));
      _range = 40;
      _isFirst = true;
   }

   void update()
   {
      
      // TODO: animate arms and hips
      if(_isFirst)
      {
         _motion.update(_skeleton, 0);
         _lFoot = _skeleton.getByName("Beta:LeftFoot")->getGlobalTranslation();
         _rFoot = _skeleton.getByName("Beta:RightFoot")->getGlobalTranslation();

         _lQuat = _skeleton.getByName("Beta:LeftFoot")->getGlobalRotation();
         _rQuat = _skeleton.getByName("Beta:RightFoot")->getGlobalRotation();

         _origRoot = _motion.getValue(0).rootPos;
         _isFirst = false;
      }

      _motion.update(_skeleton, elapsedTime());

      _lhandTarget = AVector3(20, 120 + (_range * sin(2*elapsedTime())), 25);
      _rhandTarget = AVector3(-20, 120 + (_range * -sin(2*elapsedTime())), 25);

      //_con.solveIKCCD(_skeleton, _skeleton.getByName("Beta:LeftFoot")->getID(), _lFoot, 2, 50, 0.1);
      //_con.solveIKCCD(_skeleton, _skeleton.getByName("Beta:RightFoot")->getID(), _rFoot, 2, 50, 0.1);

      AVector3 rootPos = _skeleton.getRoot()->getGlobalTranslation();
      rootPos[0] = _origRoot[0] + 3 * sin(2*elapsedTime());
      rootPos[1] = _origRoot[1] - (8 * fabs(cos(2*elapsedTime())) ) - 10;
      //rootPos[1] += 5 * sin(2*elapsedTime());

      _skeleton.getRoot()->setLocalTranslation(rootPos);
      _skeleton.getRoot()->fk();

      _con.solveIKCCD(_skeleton, _skeleton.getByName("Beta:RightHand")->getID(), _rhandTarget, 2, 50, 0.1);
      _con.solveIKCCD(_skeleton, _skeleton.getByName("Beta:LeftHand")->getID(), _lhandTarget, 2, 50, 0.1);

      _con.solveIKAnalytic(_skeleton, _skeleton.getByName("Beta:LeftFoot")->getID(), _lFoot);
      _con.solveIKAnalytic(_skeleton, _skeleton.getByName("Beta:RightFoot")->getID(), _rFoot);

      _skeleton.getByName("Beta:LeftFoot")->setLocalRotation(_skeleton.getByName("Beta:LeftFoot")->getLocal2Global().inverse().rotation * _lQuat);
      _skeleton.getByName("Beta:RightFoot")->setLocalRotation(_skeleton.getByName("Beta:RightFoot")->getLocal2Global().inverse().rotation * _rQuat);

      _skeleton.getByName("Beta:LeftFoot")->fk();
      _skeleton.getByName("Beta:RightFoot")->fk();
   }

   void draw()
   {  
      _drawer.draw(_skeleton);
      ASetMaterial(AVector3(0,0,1));
      ADrawSphere(_lhandTarget, 5);
      ADrawSphere(_rhandTarget, 5);
   }

protected:
   ACyclops _drawer;
   ASkeleton _skeleton;
   AMotion _motion;
   AIKController _con;

   // Hand target positions
   AVector3 _lhandTarget;
   AVector3 _rhandTarget;
   AVector3 _lFoot;
   AVector3 _rFoot;
   AVector3 _origRoot;
   AQuaternion _lQuat;
   AQuaternion _rQuat;
   bool _isFirst;

   float _range;
};

int main(int argc, char** argv)
{
   ADancer viewer;
   viewer.init(argc, argv);
   viewer.run();
   return 0;
}

