#include "AFramework.h"
#include "AGLObjects.h" // Helpers for drawing shapes
#include <random>
#include <functional>

class CircleExample : public AFramework
{
public:
   CircleExample() : AFramework(AFramework::Orthographic) // calls base class ctor
   {
   }

   virtual void setup() 
   {
   }

   virtual void update() 
   {
        _theta += dt();
   }

   virtual void draw() 
   {
        ASetColor(AVector3(1,0,0));

        double x = 100 * cos(_theta);
        double y = 100 * sin(_theta);
        AVector3 center(getWidth() * 0.5, getHeight() * 0.5, 0.0);
        ADrawSphere(center + AVector3(x,y,0), 25);
   }

private:
   double _theta;
};

int main(int argc, char** argv)
{
   CircleExample viewer;
   viewer.init(argc, argv);
   viewer.run();
   return 0;
}
