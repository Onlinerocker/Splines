#include "AnimationToolkit.h"
#include "AFramework.h"
#include "AGLObjects.h"
#include "GL/glew.h"
#include "GL/glut.h"
#include <algorithm>
#include <string>
#include <ode/ode.h>

class ABoxSim1 : public AFramework
{
public:
   ABoxSim1() : AFramework(AFramework::Perspective) {}

   virtual ~ABoxSim1() 
   {
      dBodyDestroy(_box);
      dWorldDestroy(_world);
      dCloseODE();
   }

   void setup()
   {
      dInitODE2(0);

      _world = dWorldCreate();
      _box = dBodyCreate(_world);
   }

   void update()
   {
      applyForces();
      printForces();
      dWorldStep(_world, 0.05);
   }

   void draw()
   {  
      const dReal* pos = dBodyGetPosition(_box);
      const dReal* ori = dBodyGetRotation(_box);

      ASetMaterial(AVector3(0,1,1));
      AVector3 boxPos(pos[0], pos[1], pos[2]);
      AMatrix3 boxOri(ori[0], ori[1], ori[2],
                      ori[4], ori[5], ori[6],
                      ori[8], ori[9], ori[10]);

      ADrawCube(boxPos, boxOri, AVector3(100,200,100));
   }

   void applyForces()
   {
   }

   void printForces()
   {
   }

protected:
   dWorldID _world;
   dBodyID _box;
};

int main(int argc, char** argv)
{
   ABoxSim1 viewer;
   viewer.init(argc, argv);
   viewer.run();
   return 0;
}

