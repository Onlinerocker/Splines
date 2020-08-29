#include "AnimationToolkit.h"
#include "AFramework.h"
#include "ASkeletonDrawer.h"
#include "GL/glew.h"
#include "GL/glut.h"
#include <algorithm>
#include <cmath>
#include <string>

class AReorient : public AFramework
{
public:
   AReorient() : AFramework(AFramework::Perspective) {}
   virtual ~AReorient() {}

   void setup()
   {
      ABVHReader reader;
      reader.load("../motions/Beta/walking.bvh", _skeleton, _motion);

      _heading = 0;
      _offset = AVector3::Zero;
      _offset[1] = _motion.getKey(0).rootPos[1];
      _time = 0;

      _reoriented = reorient(_motion, _offset, _heading);
   }

   AMotion reorient(const AMotion& motion, const AVector3& pos, double heading)
   {
      AMotion result = motion;
      APose pose = result.getKey(0);
      AQuaternion quat = AQuaternion(AVector3(0,1,0), heading);

      AVector3 offset = pos - pose.rootPos;
      AQuaternion quatOffset = quat * pose.jointRots[0].inverse();
        
      pose.rootPos = pos;
      pose.jointRots[0] = quat;
      result.editKey(0, pose);

      ATransform transOffset = ATransform(quatOffset, offset);

      for(int x=1; x<result.getNumKeys(); x++)
      {
         pose = result.getKey(x);

         ATransform newTrans = transOffset * ATransform(pose.jointRots[0], pose.rootPos);

         pose.rootPos = newTrans.translation;        
         pose.jointRots[0] = newTrans.rotation;

         result.editKey(x, pose);
      }

      return result;
   }

   void update()
   {
      _time += dt() * 0.5;
      _reoriented.update(_skeleton, _time);
   }

   void draw()
   {  
      ASkeletonDrawer drawer;
      drawer.draw(_skeleton);
   }

   void keyPress(unsigned char key, int specialKey, int x, int y) 
   {
      if (specialKey == GLUT_KEY_LEFT)
      {
         _heading += M_PI/8;
         _reoriented = reorient(_motion, _offset, _heading);
         _time = 0;
      }
      else if (specialKey == GLUT_KEY_RIGHT)
      {
         _heading -= M_PI/8;
         _reoriented = reorient(_motion, _offset, _heading);
         _time = 0;
      }

      if (key == 'w')
      {
         _offset[2] += 25;
         _reoriented = reorient(_motion, _offset, _heading);
         std::cout << _offset << std::endl;
         _time = 0;
      }
      else if (key == 's')
      {
         _offset[2] -= 25;
         _reoriented = reorient(_motion, _offset, _heading);
         _time = 0;
         std::cout << _offset << std::endl;
      }
      else if (key == 'a')
      {
         _offset[0] += 25;
         _reoriented = reorient(_motion, _offset, _heading);
         _time = 0;
         std::cout << _offset << std::endl;
      }
      else if (key == 'd')
      {
         _offset[0] -= 25;
         _reoriented = reorient(_motion, _offset, _heading);
         _time = 0;
         std::cout << _offset << std::endl;
      }
   }

   ASkeleton _skeleton;
   AMotion _motion;
   AMotion _reoriented;
   AVector3 _offset;
   double _heading;
   double _time;
};

int main(int argc, char** argv)
{
   AReorient viewer;
   viewer.init(argc, argv);
   viewer.run();
   return 0;
}

