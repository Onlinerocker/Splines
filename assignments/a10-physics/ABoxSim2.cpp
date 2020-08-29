#include "AnimationToolkit.h"
#include "AFramework.h"
#include "AGLObjects.h"
#include "GL/glew.h"
#include "GL/glut.h"
#include <algorithm>
#include <string>
#include <ode/ode.h>

class ABoxSim2 : public AFramework
{
public:
   ABoxSim2() : AFramework(AFramework::Perspective) {}

   virtual ~ABoxSim2() 
   {
      dBodyDestroy(_boxPhysics);
      dWorldDestroy(_world);
      dSpaceDestroy(_space);
      dCloseODE();
   }

   void setup()
   {
      dInitODE2(0);

      _world = dWorldCreate();
      _space = dSweepAndPruneSpaceCreate(0, dSAP_AXES_XYZ);
      _ground = dCreatePlane(_space, 0,1,0,0);
      _contacts = dJointGroupCreate(0);

      dWorldSetGravity(_world, 0, -10, 0);

      // Define the mass, center of mass, inertia tensor for a box shape
      double mass = 5;
      dMass boxMass;
      dMassSetBox(&boxMass, 1 /*density*/, _boxSize, _boxSize, _boxSize);
      dMassAdjust(&boxMass, mass); // set the total mass 

      // Create dynamically simulated box with the given mass
      // Initial position = (0,0,0)^T
      _boxPhysics = dBodyCreate(_world);
      dBodySetPosition(_boxPhysics, 0, 300, 0);
      dBodySetMass(_boxPhysics, &boxMass);

      // Create box geometry to use for collisions
      _boxGeom = dCreateBox(_space, _boxSize, _boxSize, _boxSize);
      dGeomSetBody(_boxGeom, _boxPhysics);
   }

   void update()
   {
      dSpaceCollide(_space, this, collideCb);
      dWorldStep(_world, 0.05);
      dJointGroupEmpty(_contacts);
   }

   void draw()
   {  
      const dReal* pos = dBodyGetPosition(_boxPhysics);
      const dReal* ori = dBodyGetRotation(_boxPhysics);

      ASetMaterial(AVector3(0,1,1));
      AVector3 boxPos(pos[0], pos[1], pos[2]);
      AMatrix3 boxOri(ori[0], ori[1], ori[2],
                      ori[4], ori[5], ori[6],
                      ori[8], ori[9], ori[10]);

      ADrawCube(boxPos, boxOri, _boxSize*AVector3(1,1,1));
   }

   static void collideCb(void* data, dGeomID o1, dGeomID o2)
   {
      ((ABoxSim2*)data)->collide(o1, o2);
   }

   void collide(dGeomID o1, dGeomID o2)
   {
      int i,n;

      dBodyID b1 = dGeomGetBody(o1);
      dBodyID b2 = dGeomGetBody(o2);
      if (b1 && b2 && dAreConnected(b1, b2))
         return;

      const int N = 4;
      dContact contact[N];
      n = dCollide (o1,o2,N,&contact[0].geom,sizeof(dContact));
      if (n > 0)
      {
         for (i=0; i<n; i++)
         {
            contact[i].surface.mode = dContactBounce;

            contact[i].surface.mu = dInfinity;
            contact[i].surface.slip1 = 0.0;
            contact[i].surface.slip2 = 0.0;
            contact[i].surface.soft_erp = 0.8;
            contact[i].surface.soft_cfm = 0.01;

            dJointID c = dJointCreateContact (_world,_contacts,contact+i);
            dJointAttach (c,dGeomGetBody(o1),dGeomGetBody(o2));
         }
      }
   }

protected:
   // Demo parameters
   double _boxSize = 50;

   // Physics simulation objects
   dWorldID _world;
   dGeomID _ground;
   dBodyID _boxPhysics;

   // Collision helpers
   dSpaceID _space;
   dGeomID _boxGeom;
   dJointGroupID _contacts;
};

int main(int argc, char** argv)
{
   ABoxSim2 viewer;
   viewer.init(argc, argv);
   viewer.run();
   return 0;
}

