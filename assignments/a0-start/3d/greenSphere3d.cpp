#include "AFramework.h"
#include "AGLObjects.h" // Helpers for drawing shapes

class GreenSphere3D : public AFramework
{
public:
   GreenSphere3D() : 
      AFramework(AFramework::Perspective) // calls base class ctor
   {
   }

   virtual void draw() //overrides draw
   {
      // colors are RGB triplets in range [0,1]
      ASetMaterial(AVector3(1,1,1));

      // draw a sphere at position (0,0,0)
      double radius = 10; 
      ADrawSphere(AVector3(0,0,0), radius);
      ADrawSphere(AVector3(0, radius + 1, 0), 7);

      yOff += (10 * mult) * dt();
      if(yOff > 10 || yOff < 0){
         mult *= -1;
      }

      ADrawSphere(AVector3(0, radius + 10 + yOff, 0), 5);
      
      ASetMaterial(AVector3(0,0,0));
      ADrawSphere(AVector3(2, radius + 10 + yOff, 5), 1);
      ADrawSphere(AVector3(-2, radius + 10 + yOff, 5), 1);

      ASetMaterial(AVector3(1,0.5,0));
      ADrawCone(AVector3(0, radius + 8 + yOff, 3), AMatrix3::Identity, AVector3(1,1,7));
   }

private:
   float yOff = 0;
   int mult = 1;
};

int main(int argc, char** argv)
{
   GreenSphere3D viewer;
   viewer.init(argc, argv);
   viewer.run();
   return 0;
}
