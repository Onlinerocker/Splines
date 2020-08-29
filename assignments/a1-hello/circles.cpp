#include "AFramework.h"
#include "AGLObjects.h" // Helpers for drawing shapes
#include <random>
#include <functional>

class Particle
{
   public:
      AVector3 pos;
      AVector3 color;
      int dir;
      double ang;

      Particle(){}

      Particle(AVector3 pos, AVector3 color, int dir, double ang)
      {
         this->pos = pos;
         this->color = color;
         this->dir = dir;
         this->ang = ang;
      }
};

class Circles : public AFramework
{
public:

   Particle** particles;
   AVector3 pallet[5] = 
   {
      AVector3(171,221,112)/255.,
      AVector3(72,141,18)/255.,
      AVector3(206,2,53)/255.,
      AVector3(246,215,215)/255.,
      AVector3(43,20,20)/255.
   };

   Circles() : AFramework(AFramework::Orthographic) // calls base class ctor
   {
      particles = new Particle*[10];
      for(int x=0; x<10; x++){
         particles[x] = new Particle[36];
      }
   }

   virtual void setup() //overrides init
   {
      int dir = 1;
      for(int rad = 0; rad < 10; rad ++){
         AVector3 center(getWidth() * 0.5, getHeight() * 0.5, 0.0);
         AVector3 col = pallet[rand() % 5];
         for(int ind=0; ind<36; ind++){
            double x = (rad * 50) * cos(dir * ADeg2Rad * (ind *10));
            double y = (rad * 50) * sin(dir * ADeg2Rad * (ind *10));
            particles[rad][ind].pos = center + AVector3(x, y, 0);
            particles[rad][ind].color = col;
            particles[rad][ind].dir = dir;
            particles[rad][ind].ang = ind*10;
         }

         dir *= -1;
      }
   }

   virtual void update() //overrides update
   {
      AVector3 center(getWidth() * 0.5, getHeight() * 0.5, 0.0);

      for(int rad = 0; rad < 10; rad ++){
         for(int ind=0; ind<36; ind++){
            particles[rad][ind].ang += (dt() * 10);
            double x = (rad * 50) * cos(particles[rad][ind].dir * ADeg2Rad * (particles[rad][ind].ang) );
            double y = (rad * 50) * sin(particles[rad][ind].dir * ADeg2Rad * (particles[rad][ind].ang) );
            particles[rad][ind].pos = center + AVector3(x, y, 0);
         }
      }
   }

   virtual void draw() //overrides draw
   {
      for(int rad=0; rad<10; rad++){
         for(int ind=0; ind<36; ind++){
            ASetColor(particles[rad][ind].color);
            ADrawSphere(particles[rad][ind].pos, 10);
         }
      }
   }

};

int main(int argc, char** argv)
{
   Circles viewer;
   viewer.init(argc, argv);
   viewer.run();
   return 0;
}
