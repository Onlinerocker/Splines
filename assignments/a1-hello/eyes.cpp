#include "AFramework.h"
#include "AGLObjects.h" // Helpers for drawing shapes

class Eyes : public AFramework
{
public:
   Eyes() : AFramework(AFramework::Orthographic) // calls base class ctor
   {
   }

   virtual void draw() //overrides draw
   {
      int radius = 50;
      AVector3 center(getWidth() * 0.5, getHeight() * 0.5, 0.0);
      ASetColor(AVector3(1,1,1));
      ADrawSphere(center - AVector3(radius + 10, 0, 0), radius);
      ADrawSphere(center + AVector3(radius + 10, 0, 0), radius);

      double x = 45 * sin(elapsedTime());
      ASetColor(AVector3(0,0,0));
      ADrawSphere(center + AVector3(radius + 10 + x,0,60), 10);
      ADrawSphere(center + AVector3(-radius - 10 + x,0,60), 10);

   }
};

int main(int argc, char** argv)
{
   Eyes viewer;
   viewer.init(argc, argv);
   viewer.run();
   return 0;
}
