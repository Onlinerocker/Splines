#include "AFramework.h"
#include "AGLObjects.h" // Helpers for drawing shapes
#include <random>
#include <functional>

class Particle
{
   public:
      AVector3 pos;
      AVector3 path;
      AVector3 color;
      double speed;

      Particle(){}

      Particle(AVector3 pos, AVector3 path, double speed)
      {
         this->pos = pos;
         this->path = path;
         this->speed = speed;
      }
};

class Velocity : public AFramework
{
public:
   Particle* particles;
   int size = 200;

   Velocity() : AFramework(AFramework::Orthographic) // calls base class ctor
   {
      srand(time(0));
      particles = new Particle[size];
   }

   virtual void setup() 
   {
      for(int x=0; x<size; x++){
         int xPos = (rand() % getWidth());
         int yPos = (rand() % getHeight());
         particles[x].pos = AVector3(xPos, yPos, 0);
         particles[x].path = AVector3(1,1,0);
         particles[x].color = AVector3(0.2 + (-0.2 + rand() % 40 / 100.0), 0.8 + (-0.2 + rand() % 40 / 100.0), 0.2 + (-0.2 + rand() % 40 / 100.0));
         particles[x].speed = (rand() % 100) + 10;
      }
   }

   virtual void update() 
   {
      for(int x=0; x<size; x++){
         if(particles[x].pos.x() > getWidth()){
            particles[x].pos = AVector3(0, particles[x].pos.y(), particles[x].pos.z());
         }

         if(particles[x].pos.y() > getHeight()){
            particles[x].pos = AVector3(particles[x].pos.x(), 0, particles[x].pos.z());
         }
         particles[x].pos += particles[x].path * particles[x].speed * dt();

      }
   }

   virtual void draw() 
   {
      for(int x=0; x<size; x++){
         ASetColor(particles[x].color);
         ADrawSphere(particles[x].pos, 10);
      }
   }
};

int main(int argc, char** argv)
{
   Velocity viewer;
   viewer.init(argc, argv);
   viewer.run();
   return 0;
}
