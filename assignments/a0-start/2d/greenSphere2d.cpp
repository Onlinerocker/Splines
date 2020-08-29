#include "AFramework.h"
#include "AGLObjects.h" // Helpers for drawing shapes

class GreenSphere2D : public AFramework
{
public:
   GreenSphere2D() : 
      AFramework(AFramework::Orthographic) // calls base class ctor
   {
   }

   virtual void draw() //overrides draw
   {
      // colors are RGB triplets in range [0,1]
      ASetColor(AVector3(0,1,0));

      // draw a sphere at center of screen
      double x = getWidth() * 0.5;
      double y = getHeight() * 0.5;
      double radius = 20; 
      ADrawSphere(AVector3(x,y,0), radius);

      ASetColor(AVector3(1,0,0));
      ADrawSphere(AVector3(x,y,radius/2 + 1), radius/2);
   }
};

int main(int argc, char** argv)
{
   GreenSphere2D viewer;
   viewer.init(argc, argv);
   viewer.run();
   return 0;
}
