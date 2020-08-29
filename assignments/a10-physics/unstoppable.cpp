#include "AnimationToolkit.h"
#include "AFramework.h"
#include "ASkeletonDrawer.h"
#include "AGLObjects.h"
#include "GL/glew.h"
#include "GL/glut.h"
#include <algorithm>
#include <string>
#include <ode/ode.h>

using namespace std;

class APhysicsViewer : public AFramework
{
public:
   APhysicsViewer() : AFramework(AFramework::Perspective) {}
   virtual ~APhysicsViewer() 
   {
      shutdownSimulation();
      dCloseODE();
   }

   void shutdownSimulation()
   {
      dJointGroupDestroy(_contacts);
      // todo: cleanup wall and kinematic objects
      dWorldDestroy(_world);
      dSpaceDestroy(_space);
   }

   dBodyID createBox(double mass, double boxSize, dWorldID world, dSpaceID space, AVector3 pos)
   {
      dMass boxMass;
      dMassSetBox(&boxMass, 1 /*density*/, boxSize, boxSize, boxSize);
      dMassAdjust(&boxMass, mass); // set the total mass 

      // Create dynamically simulated box with the given mass
      dBodyID boxDynamic = dBodyCreate(world);
      dBodySetPosition(boxDynamic, pos[0], pos[1], pos[2]);
      dBodySetMass(boxDynamic, &boxMass);

      // create collision object for physics box 
      dGeomID boxGeomDynamic = dCreateBox(space, boxSize, boxSize, boxSize);
      dGeomSetBody(boxGeomDynamic, boxDynamic);

      return boxDynamic;
   }

   dBodyID createKinSphere(double mass, double radius, dWorldID world, dSpaceID space, AVector3 pos)
   {
      dMass sphereMass;
      dMassSetSphere(&sphereMass, 1, radius);
      dMassAdjust(&sphereMass, mass);

      dBodyID sphereKin = dBodyCreate(world);
      dBodySetPosition(sphereKin, pos[0], pos[1], pos[2]);
      dBodySetKinematic(sphereKin);

      dGeomID sphereGeomKin = dCreateSphere(space, radius);
      dGeomSetBody(sphereGeomKin, sphereKin);

      return sphereKin;
   }

   void drawBox(dBodyID box, const AVector3& color, double size)
   {
      const dReal* pos = dBodyGetPosition(box);
      const dReal* ori = dBodyGetRotation(box);

      ASetMaterial(color);
      AVector3 boxPos(pos[0], pos[1], pos[2]);
      AMatrix3 boxOri(ori[0], ori[1], ori[2],
                      ori[4], ori[5], ori[6],
                      ori[8], ori[9], ori[10]);

      ADrawCube(boxPos, boxOri, size*AVector3(1,1,1));
   }

   void drawSphere(dBodyID sphere,  const AVector3& color, double radius)
   {
      const dReal* pos = dBodyGetPosition(sphere);
      AVector3 posVec = AVector3(pos[0], pos[1], pos[2]);

      ASetMaterial(color);
      ADrawSphere(posVec, radius);
   }

   void createAndAddBox(double mass, double boxSize, dWorldID world, dSpaceID space, AVector3 pos)
   {
      dBodyID box = createBox(mass, boxSize, world, space, pos);
      boxes.push_back(box);
      boxSizes.push_back(boxSize);
   }

   void setupSimulation()
   {
      _time = 0;
      _world = dWorldCreate();
      _space = dSweepAndPruneSpaceCreate(0, dSAP_AXES_XYZ);
      _ground = dCreatePlane(_space, 0,1,0,0);
      _contacts = dJointGroupCreate(0);

      dWorldSetGravity(_world, 0, -100, 0);

      joints.clear();
      boxes.clear();
      boxSizes.clear();

      double start = -75;
      double end = 100;
      
      for(double y = 50; y < 250; y+=55)
      {
         for(double x = start; x < end; x+=52)
         {
            createAndAddBox(50, 50, _world, _space, AVector3(x, y, 100));
         }
         start += 25;
         end -= 25;
      }


      for(int j = 0; j < _skeleton.getNumJoints(); j++)
      {
         //createKinSphere(double mass, double radius, dWorldID world, dSpaceID space, AVector3 pos)
         AVector3 pos = _skeleton.getByID(j)->getGlobalTranslation();
         dBodyID sphere = createKinSphere(_jointMass, _jointSize, _world, _space, pos);
         joints.push_back(sphere);
      }
   }

   void setup()
   {
      _drawPhysics = false;

      ABVHReader reader;
      reader.load("../motions/Beta/back_flip_to_uppercut.bvh", _skeleton, _motion);
      _motion.update(_skeleton, 0);

      dInitODE2(0);
      setupSimulation();
   }

   void update()
   {
      _time += dt();
      _motion.update(_skeleton, _time, false);

      // todo: update kinematic objects
      for(int j = 0; j < _skeleton.getNumJoints(); j++)
      {
         AVector3 pos = _skeleton.getByID(j)->getGlobalTranslation();
         dBodySetPosition(joints[j], pos[0], pos[1], pos[2]);
      }

      dSpaceCollide(_space, this, collideCb);
      dWorldStep(_world, 0.05);
      dJointGroupEmpty(_contacts);
   }

   void draw()
   {  
      if (_drawPhysics)
      {
         // todo: draw kinematic bodies
         for(int j = 0; j < joints.size(); j++)
         {
            drawSphere(joints[j], AVector3(0,0,1), 5);
         }
      }
      else
      {
         _drawer.draw(_skeleton);
      }

      // todo: draw dynamic bodies
      for(int x=0; x < boxes.size(); x++)
      {
         drawBox(boxes[x], AVector3(1,0,0), 50);
      }
   }

   void keyPress(unsigned char key, int specialKey, int x, int y) 
   {
      if (key == ' ') 
      {
         shutdownSimulation();
         setupSimulation();
      }
      else if (key == 'd') _drawPhysics = !_drawPhysics;
   }

   static void collideCb(void* data, dGeomID o1, dGeomID o2)
   {
      ((APhysicsViewer*)data)->collide(o1, o2);
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

            contact[i].surface.mu = 1000; 
            contact[i].surface.slip1 = 0.0;
            contact[i].surface.slip2 = 0.0;
            contact[i].surface.soft_erp = 0.8;
            contact[i].surface.soft_cfm = 0.01;

            dJointID c = dJointCreateContact (_world,_contacts,contact+i);
            dJointAttach (c,dGeomGetBody(o1),dGeomGetBody(o2));
         }
      }
   }

private:

   ASkeletonDrawer _drawer;
   ASkeleton _skeleton;
   AMotion _motion;
   dSpaceID _space;
   dWorldID _world;
   dGeomID _ground;
   dJointGroupID _contacts;

   vector<dBodyID> boxes;
   vector<double> boxSizes;

   vector<dBodyID> joints;
   double _jointSize = 2;
   double _jointMass = 5;

   bool _drawPhysics;
   double _time;
};

int main(int argc, char** argv)
{
   APhysicsViewer viewer;
   viewer.init(argc, argv);
   viewer.run();
   return 0;
}

