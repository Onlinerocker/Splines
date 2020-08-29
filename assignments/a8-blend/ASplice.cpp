#include "AnimationToolkit.h"
#include "AFramework.h"
#include "ASkeletonDrawer.h"
#include "GL/glew.h"
#include "GL/glut.h"
#include <algorithm>
#include <string>

class ASplice : public AFramework
{
public:
   ASplice() : AFramework(AFramework::Perspective) {}
   virtual ~ASplice() {}

   void setup()
   {
      _alpha = 0;

      ABVHReader reader;
      reader.load("../motions/Beta/walking.bvh", _skeleton, _lower);
      reader.load("../motions/Beta/gangnam_style.bvh", _skeleton, _upper);
      _splice = spliceUpperBody(_lower, _upper, _alpha);
   }

   APose setPoseToChildren(APose orig, APose toChange, AJoint *joint)
   {
      if(joint->getName() == "Beta:Spine1") return toChange;

      APose newPose = toChange;
      newPose.jointRots[joint->getID()] = orig.jointRots[joint->getID()];
      newPose.rootPos = orig.rootPos;

      for(int x=0; x<joint->getNumChildren(); x++)
      {
         newPose = setPoseToChildren(orig, newPose, joint->getChildAt(x));
      }

      return newPose;
   }

   AMotion spliceUpperBody(const AMotion& orig, const AMotion& upper, double alpha)
   {
      AMotion result;
      result.setFramerate(orig.getFramerate());

      for(int x=0; x<orig.getNumKeys(); x++)
      {
         result.appendKey(APose::Lerp(upper.getKey(120 + x), orig.getKey(x), alpha));
      }

      AJoint* hips = _skeleton.getByName("Beta:Hips");
      for(int x=0; x<result.getNumKeys(); x++)
      {
         APose newPose = setPoseToChildren(orig.getKey(x), result.getKey(x), hips);
         result.editKey(x, newPose);
      }

      return result;
   }

   void update()
   {
      _splice.update(_skeleton, elapsedTime() * 0.5);
   }

   void draw()
   {  
      ASkeletonDrawer drawer;
      drawer.draw(_skeleton);
   }

   void keyPress(unsigned char key, int specialKey, int x, int y) 
   {
      if (specialKey == GLUT_KEY_UP)
      {
         _alpha = std::min(_alpha+0.05, 1.0);
         _splice = spliceUpperBody(_lower, _upper, _alpha);
      }
      else if (specialKey == GLUT_KEY_DOWN)
      {
         _alpha = std::max(_alpha-0.05, 0.0);
         _splice = spliceUpperBody(_lower, _upper, _alpha);
      }

      if (key == '0')
      {
         _alpha = 0.0;
         _splice = spliceUpperBody(_lower, _upper, _alpha);
      }
      else if (key == '1')
      {
         _alpha = 0.5;
         _splice = spliceUpperBody(_lower, _upper, _alpha);
      }
      else if (key == '2')
      {
         _alpha = 1.0;
         _splice = spliceUpperBody(_lower, _upper, _alpha);
      }
   }

   ASkeleton _skeleton;
   AMotion _upper;
   AMotion _lower;
   AMotion _splice;
   double _alpha;
};

int main(int argc, char** argv)
{
   ASplice viewer;
   viewer.init(argc, argv);
   viewer.run();
   return 0;
}

