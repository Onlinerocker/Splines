#include "AFramework.h"
#include "AGLObjects.h" // Helpers for drawing shapes
#include <random>
#include <functional>

class CircleLerp1 : public AFramework
{
public:
   CircleLerp1() : AFramework(AFramework::Perspective) 
   {
   }

   virtual void draw() 
   {
        AVector3 start = AVector3(1,0,0);
        AVector3 end = AVector3(0,0,1);

        double duration = 8;
        double t = elapsedTime()/duration;
        AVector3 color = (1-t) * start + t * end;

        ASetMaterial(color);
        ADrawSphere(AVector3(0,0,0), 50);
   }
};

int main(int argc, char** argv)
{
   CircleLerp1 viewer;
   viewer.init(argc, argv);
   viewer.run();
   return 0;
}
