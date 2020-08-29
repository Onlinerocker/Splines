#include "AFramework.h"
#include "AGLObjects.h" // Helpers for drawing shapes
#include <random>
#include <functional>

class ParticleExample : public AFramework
{
public:
   ParticleExample() : AFramework(AFramework::Orthographic) // calls base class ctor
   {
   }

   virtual void setup() 
   {
   }

   virtual void update() 
   {
      _pos = _pos + dt() * AVector3(100,100,0);
   }

   virtual void draw() //overrides draw
   {
      ASetColor(AVector3(1,0,0));
      ADrawSphere(_pos, 10);
   }

private:
   AVector3 _pos;
};

int main(int argc, char** argv)
{
   ParticleExample viewer;
   viewer.init(argc, argv);
   viewer.run();
   return 0;
}
