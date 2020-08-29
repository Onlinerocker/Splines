#include "AFramework.h"
#include "AGLObjects.h" // Helpers for drawing shapes
#include <random>
#include <functional>

class Particle
{
   public:
      AVector3 pos;
      double size;
      int colInd;
      double timeToCol;
      AVector3 color;

      Particle(){}

      Particle(AVector3 pos, int color, double size)
      {
         this->pos = pos;
         this->colInd = color;
         this->size = size;
         this->timeToCol = 0;
      }
};

class Bonus : public AFramework
{
public:

   std::vector<Particle*> parts;
   AVector3 pallet[5] = 
   {
      AVector3(171,221,112)/255.,
      AVector3(72,141,18)/255.,
      AVector3(206,2,53)/255.,
      AVector3(246,215,215)/255.,
      AVector3(43,20,20)/255.
   };

   Bonus() : AFramework(AFramework::Orthographic) // calls base class ctor
   {

   }

   virtual void setup() //overrides init
   {

   }

   virtual void update() //overrides update
   {

   }

   virtual void draw() //overrides draw
   {
       for(int i=0; i<parts.size(); i++){
            parts[i]->color = pallet[parts[i]->colInd] * (1 - parts[i]->timeToCol) + pallet[parts[i]->colInd + 1] * parts[i]->timeToCol;
            parts[i]->timeToCol += dt();
            if(parts[i]->timeToCol >= 1){
                parts[i]->timeToCol = 0;
                parts[i]->colInd++;
                if(parts[i]->colInd >= 5)
                    parts[i]->colInd = 0;
            }

            ASetColor(parts[i]->color);
            ADrawSphere(parts[i]->pos, parts[i]->size);
       }

      AVector3 target = AVector3(_mouseX, _mouseY, 0);
      ASetColor(AVector3(1,0,0));
      ADrawSphere(target, 5);
      for(int i=0; i<parts.size(); i++){
          if(parts[i]->pos == target)
            return;
      }
      Particle *part = new Particle(target, (rand() % 5), (rand() % 20));
      parts.push_back(part);


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
   Bonus viewer;
   viewer.init(argc, argv);
   viewer.run();
   return 0;
}
