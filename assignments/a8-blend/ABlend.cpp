#include "AnimationToolkit.h"
#include "AFramework.h"
#include "ASkeletonDrawer.h"
#include "GL/glew.h"
#include "GL/glut.h"
#include <algorithm>
#include <string>

class ABlend : public AFramework
{
public:
   ABlend() : AFramework(AFramework::Perspective) {}
   virtual ~ABlend() {}

   void setup()
   {
      _alpha = 0.5;
      ABVHReader reader;
      reader.load("../motions/Beta/left_strafe_walking.bvh", _skeleton, _motion1);
      reader.load("../motions/Beta/walking.bvh", _skeleton, _motion2);

      _blend = blend(_motion1, _motion2, _alpha);

      std::cout << "JOINTS" << std::endl;
      for(int x=0; x<_skeleton.getNumJoints(); x++)
      {
         std::cout << _skeleton.getByID(x)->getName() << std::endl;
      }
   }

   AMotion blend(const AMotion& m1, const AMotion& m2, double alpha)
   {
      double dur = (m1.getDuration() * (1-alpha)) + m2.getDuration() * alpha;
      AMotion blend;
      blend.setFramerate(m1.getFramerate());

      for(double x=0; x<dur; x+= m1.getDeltaTime())
      {
         APose pose1 = m1.getValue(x / dur, false);
         APose pose2 = m2.getValue(x / dur, false);
         blend.appendKey(APose::Lerp(pose1, pose2, alpha));
      }
      // todo: your code here
      return blend;
   }

   void draw()
   {  
      drawMotion(_motion2, AVector3(-150,0,0));
      drawMotion(_motion1, AVector3(150,0,0));
      drawMotion(_blend, AVector3(0,0,0));
   }

   void update()
   {

   }

   void drawMotion(const AMotion& m, const AVector3& offset)
   {
      double t = elapsedTime() * 0.5;
      double time = m.getNormalizedDuration(t) * m.getDuration();
      m.update(_skeleton, time, false);

      ASkeletonDrawer drawer;
      drawer.setOffsetPosition(offset);
      drawer.draw(_skeleton);
   }

   void keyPress(unsigned char key, int specialKey, int x, int y) 
   {
      if (specialKey == GLUT_KEY_UP)
      {
         _alpha = std::min(_alpha+0.05, 1.0);
         _blend = blend(_motion1, _motion2, _alpha);
      }
      else if (specialKey == GLUT_KEY_DOWN)
      {
         _alpha = std::max(_alpha-0.05, 0.0);
         _blend = blend(_motion1, _motion2, _alpha);
      }
   }

protected:
   ASkeleton _skeleton;
   AMotion _blend;
   AMotion _motion1;
   AMotion _motion2;
   double _alpha;
};

int main(int argc, char** argv)
{
   ABlend viewer;
   viewer.init(argc, argv);
   viewer.run();
   return 0;
}

