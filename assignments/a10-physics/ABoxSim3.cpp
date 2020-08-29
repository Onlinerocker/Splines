#include "AnimationToolkit.h"
#include "AFramework.h"
#include "AGLObjects.h"
#include "GL/glew.h"
#include "GL/glut.h"
#include <algorithm>
#include <string>
#include <ode/ode.h>

class ABoxSim3 : public AFramework
{
public:
   ABoxSim3() : AFramework(AFramework::Perspective) {}

   virtual ~ABoxSim3() 
   {
      dBodyDestroy(_boxDynamic);
      dBodyDestroy(_boxKinematic);
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
      double mass = 50;
      dMass boxMass;
      dMassSetBox(&boxMass, 1 /*density*/, _boxSize, _boxSize, _boxSize);
      dMassAdjust(&boxMass, mass); // set the total mass 

      // Create dynamically simulated box with the given mass
      _boxDynamic = dBodyCreate(_world);
      dBodySetPosition(_boxDynamic, 200, _boxSize, 0);
      dBodySetMass(_boxDynamic, &boxMass);

      // create collision object for physics box 
      _boxGeomDynamic = dCreateBox(_space, _boxSize, _boxSize, _boxSize);
      dGeomSetBody(_boxGeomDynamic, _boxDynamic);

      // Create kinematically simulated box 
      _boxKinematic = dBodyCreate(_world);
      dBodySetPosition(_boxKinematic, 0, _boxSize * 0.5, 0);
      dBodySetKinematic(_boxKinematic);

      // Create collision box for kinematic box
      _boxGeomKinematic = dCreateBox(_space, _boxSize, _boxSize, _boxSize);
      dGeomSetBody(_boxGeomKinematic, _boxKinematic);
   }

   void update()
   {
      dSpaceCollide(_space, this, collideCb);
      dWorldStep(_world, 0.05);
      dJointGroupEmpty(_contacts);
   }

   void drawBox(dBodyID box, const AVector3& color)
   {
      const dReal* pos = dBodyGetPosition(box);
      const dReal* ori = dBodyGetRotation(box);

      ASetMaterial(color);
      AVector3 boxPos(pos[0], pos[1], pos[2]);
      AMatrix3 boxOri(ori[0], ori[1], ori[2],
                      ori[4], ori[5], ori[6],
                      ori[8], ori[9], ori[10]);

      ADrawCube(AVector3(0,0,0), boxOri, _boxSize*AVector3(1,1,1));
   }

   void draw()
   {  
      ADrawCube(AVector3(0,0,0), AQuaternion::Identity, _boxSize*AVector3(1,1,1));
      drawBox(_boxDynamic, AVector3(0,1,1));
      drawBox(_boxKinematic, AVector3(0.2,0.5,1));
   }

   void keyPress(unsigned char key, int specialKey, int x, int y) 
   {
      double step = 5;
      if (key == 'w') 
      {
         const dReal* pos = dBodyGetPosition(_boxKinematic);
         dBodySetPosition(_boxKinematic, pos[0]+step, pos[1], pos[2]);
      }
      if (key == 's') 
      {
         const dReal* pos = dBodyGetPosition(_boxKinematic);
         dBodySetPosition(_boxKinematic, pos[0]-step, pos[1], pos[2]);
      }
      if (key == 'a') 
      {
         const dReal* pos = dBodyGetPosition(_boxKinematic);
         dBodySetPosition(_boxKinematic, pos[0], pos[1], pos[2]-step);
      }
      if (key == 'd') 
      {
         const dReal* pos = dBodyGetPosition(_boxKinematic);
         dBodySetPosition(_boxKinematic, pos[0], pos[1], pos[2]+step);
      }
   }


   static void collideCb(void* data, dGeomID o1, dGeomID o2)
   {
      ((ABoxSim3*)data)->collide(o1, o2);
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

   // Physics simulation objects (kinematic and dynamic)
   dWorldID _world;
   dGeomID _ground;
   dBodyID _boxDynamic;
   dBodyID _boxKinematic;

   // Collision helpers
   dSpaceID _space;
   dGeomID _boxGeomDynamic;
   dGeomID _boxGeomKinematic;
   dJointGroupID _contacts;
};

int main(int argc, char** argv)
{
   ABoxSim3 viewer;
   viewer.init(argc, argv);
   viewer.run();
   return 0;
}

