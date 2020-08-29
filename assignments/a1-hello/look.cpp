#include "AFramework.h"
#include "AGLObjects.h" // Helpers for drawing shapes

class Look : public AFramework
{
public:
   Look() : AFramework(AFramework::Orthographic) // calls base class ctor
   {
   }

   virtual void setup() 
   {
      _mouseX = getWidth() * 0.5;
      _mouseY = getHeight() * 0.5;
   }

   virtual void draw() //overrides draw
   {
      // Draw the target
      AVector3 target = AVector3(_mouseX, _mouseY, 0);
      ASetColor(AVector3(1,0,0));
      ADrawSphere(target, 5);

      int radius = 50;
      AVector3 center(getWidth() * 0.5, getHeight() * 0.5, 0.0);
      ASetColor(AVector3(1,1,1));
      ADrawSphere(center - AVector3(radius + 10, 0, 0), radius);
      ADrawSphere(center + AVector3(radius + 10, 0, 0), radius);

      AVector3 relPos = target - (center + AVector3(radius + 10, 0, 60));

      double theta = atan2(relPos.y(), relPos.x());
      double x = cos(theta) * 30;
      double y = sin(theta) * 30;

      ASetColor(AVector3(0,0,0));
      ADrawSphere(center + AVector3(radius + 10 + x, y, 60), 10);

      relPos = target - (center + AVector3(-radius - 10, 0, 60));

      theta = atan2(relPos.y(), relPos.x());
      x = cos(theta) * 30;
      y = sin(theta) * 30;

      ADrawSphere(center + AVector3(-radius - 10 + x, y, 60), 10);

   }

   void mouseMove(int x, int y) 
   {
       _mouseX = x;
       _mouseY = getHeight() - y;
   }

private:
    int _mouseX;
    int _mouseY;
};

int main(int argc, char** argv)
{
   Look viewer;
   viewer.init(argc, argv);
   viewer.run();
   return 0;
}
