#include <random>
#include <functional>
#include "AFramework.h"
#include "AMrFancy.h"
#include "AnimationToolkit.h"

class AFancy : public AFramework
{
public:
   AFancy() : AFramework(AFramework::Perspective) {}
   virtual ~AFancy() {}

   virtual void setup()
   {
      ABVHReader reader;
      reader.load("../motions/Beta/idle.bvh", _skeleton, _motion);
      _drawer.setColor(AVector3(1, 1, 0));
   }

   virtual void update()
   {
      APose pose = _motion.getValue(elapsedTime());
      _skeleton.setPose(pose);
   }

   virtual void draw()
   {
      _drawer.draw(_skeleton);
   }

protected:
   AMrFancy _drawer;
   AMotion _motion;
   ASkeleton _skeleton;
   bool _paused;
};

int main(int argc, char** argv)
{
   AFancy viewer;
   viewer.init(argc, argv);
   viewer.run();
}

