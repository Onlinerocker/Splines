#include <random>
#include <functional>
#include "AFramework.h"
#include "ADevil.h"
#include "AnimationToolkit.h"

class Thriller : public AFramework
{
public:
   Thriller() : AFramework(AFramework::Perspective) {}
   virtual ~Thriller() {}

   virtual void setup()
   {
      ABVHReader reader;
      reader.load("../motions/Warrok/WarrokThriller.bvh", 
         _skeleton, _motion);
      _drawer.setColor(AVector3(0.5, 0, 0));

      for(int x=0; x<12; x++)
      {
         ADevil devil;
         devil.setOffsetPosition(AVector3(-200 + random() % 400, 0, -200 + random() % 400));
         devil.setColor(AVector3(random() % 100 / 100.0f, random() % 100 / 100.0f, random() % 100 / 100.0f));
         devil.setScale(0.5 + random() % 50 / 100.0f);
         _drawers.push_back(devil);
      }
   }

   virtual void update()
   {
      if (!_paused)
      {
         APose pose = _motion.getValue(elapsedTime());
         _skeleton.setPose(pose);
      }
   }

   virtual void draw()
   {
      //_drawer.draw(_skeleton);

      for(int x=0; x<10; x++)
      {
         _drawers[x].draw(_skeleton);
      }
   }

   virtual void keyPress(unsigned char key, int specialKey, int x, int y)
   {
      if (key == 'p') _paused = !_paused;
   }

protected:
   ADevil _drawer;
   AMotion _motion;
   ASkeleton _skeleton;
   bool _paused;

   std::vector<ADevil> _drawers;
};

int main(int argc, char** argv)
{
   Thriller viewer;
   viewer.init(argc, argv);
   viewer.run();
}

