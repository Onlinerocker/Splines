#include "AFramework.h"
#include "AGLObjects.h" // Helpers for drawing shapes
#include <random>
#include <functional>

class CircleLerp2 : public AFramework
{
public:
   CircleLerp2() : AFramework(AFramework::Perspective) 
   {
   }

   virtual void draw() 
   {
       AVector3 startP = AVector3(100,0,0);
       AVector3 endP = AVector3(0,0,100);   

       AVector3 startC = AVector3(1,0,0);
       AVector3 endC = AVector3(0,0,1);   

       int numSpheres = 5;
       double radius = 5;
       double deltaT = 1.0/numSpheres;
       for (double t = 0; t < 1; t += deltaT)
       {
            AVector3 p = (1-t)* startP + t*endP;
            AVector3 c = (1-t)* startC + t*endC;
            ASetMaterial(c);
            ADrawSphere(p, radius);
       }
       ASetMaterial(endC);
       ADrawSphere(endP, radius);
   }
};

int main(int argc, char** argv)
{
   CircleLerp2 viewer;
   viewer.init(argc, argv);
   viewer.run();
   return 0;
}

