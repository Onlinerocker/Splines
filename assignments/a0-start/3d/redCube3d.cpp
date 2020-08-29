#include "AFramework.h"
#include "AGLObjects.h" // Helpers for drawing shapes

class RedCube2D : public AFramework
{
public:
   RedCube2D() : 
      AFramework(AFramework::Perspective) // calls base class ctor
   {
   }

   virtual void draw() //overrides draw
   {
      // colors are RGB triplets in range [0,1]
      ASetMaterial(AVector3(1,0,0));

      // let's not rotate the cube => pass identity for rotation
      // let's make the x,y,z sides of the cube each by 10 units
      ADrawCube(AVector3(0,0,0), AMatrix3::Identity, AVector3(10,10,10));
   }
};

int main(int argc, char** argv)
{
   RedCube2D viewer;
   viewer.init(argc, argv);
   viewer.run();
   return 0;
}
