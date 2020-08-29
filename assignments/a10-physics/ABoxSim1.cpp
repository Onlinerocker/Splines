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

      // Define the mass, center of mass, inertia tensor for a box shape
      dMass boxMass;
      dMassSetBox(&boxMass, 1 /*density*/, _boxSize, _boxSize, _boxSize);
      dMassAdjust(&boxMass, _mass); // set the total mass 

      // Create dynamically simulated box with the given mass
      // Initial position = (0,0,0)^T
      _box = dBodyCreate(_world);
      dBodySetPosition(_box, 0, 0, 0);
      dBodySetMass(_box, &boxMass);
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

      ADrawCube(boxPos, boxOri, _boxSize*AVector3(1,1,1));
   }

   void applyForces()
   {
      AVector3 f1(0, 0, _strength);
      AVector3 r1(-3, 0, 2); 
      dBodyAddRelForceAtRelPos(_box, 
         f1.x(), f1.y(), f1.z(), 
         r1.x(), r1.y(), r1.z());

      AVector3 f2(0, 0, _strength);
      AVector3 r2(3, 0, 2); 
      dBodyAddRelForceAtRelPos(_box, 
         f2.x(), f2.y(), f2.z(), 
         r2.x(), r2.y(), r2.z());
   }

   void printForces()
   {
      // output force and torque
      // expect: force = (0,0,strength*2); torque = 0
      const dReal* force = dBodyGetForce(_box);
      AVector3 F(force[0], force[1], force[2]);
      std::cout << "force = " << F << std::endl;

      const dReal* torque = dBodyGetTorque(_box);
      AVector3 t(torque[0], torque[1], torque[2]);
      std::cout << "torque = " << t << std::endl;
   }

protected:
   dWorldID _world;

   dBodyID _box;
   double _boxSize = 50.0;
   double _strength = 10.0;
   double _mass = 5.0;
};

int main(int argc, char** argv)
{
   ABoxSim1 viewer;
   viewer.init(argc, argv);
   viewer.run();
   return 0;
}

