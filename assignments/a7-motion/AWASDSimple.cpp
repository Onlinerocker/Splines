#include "AFramework.h"
#include "AApp3D.h"
#include "AGLObjects.h"
#include "ACamera.h"
#include "AnimationToolkit.h"
#include "ASkeletonDrawer.h"
#include <iostream>
#include <cmath>

class WASDSimple : public AFramework
{
public:
   WASDSimple() : AFramework(AFramework::Perspective) {}

   virtual void setup()
   {
      /*    void crossfade(AMotion& motion1, AMotion& motion2,
        int startKeyId, int endKeyId, int numBlendFrames, AMotion& blend); */

      AApp3D::GridSize = 5000;
      ABVHReader reader;
      reader.load("../motions/Beta/walking.bvh", _skeleton, _walk);
      reader.load("../motions/Beta/jump.bvh", _skeleton, _jump);
      _drawer.setShowAxis(true);
      _pos = _walk.getValue(0, true).rootPos;

      jumpMax = 150;
      jumped = 0;
      _jumping = false;
      walkElap = 0;
      jumpElap = 0;
   }

   virtual void draw()
   {
      _drawer.draw(_skeleton);

      // draw heading
      AVector3 startPos = _skeleton.getRoot()->getGlobalTranslation();
      startPos[1] = 0;
      AVector3 endPos = startPos + AVector3(sin(_heading) * 100, 0, cos(_heading) * 100);
      _forward = endPos - startPos;
      _forward = _forward.normalized();

      ASetColor(AVector3(0,1,0));
      ADrawLine(startPos, endPos);
   }

   virtual void update()
   {

      ACamera* camera = getCamera();
      camera->set(_pos + (_forward * -200) + AVector3(0,100,0), _pos, AVector3(0,1,0) /*up*/);

      if(_jumping)
      {
         APose jumpPose = _jump.getValue(jumpElap, true);

         jumpPose.rootPos = _pos;
         jumpPose.jointRots[0] = AQuaternion(AVector3(0,1,0), _heading) * jumpPose.jointRots[0];
         //_skeleton.getRoot()->setLocalRotation(AQuaternion(AVector3(0,1,0), _heading));

         _skeleton.setPose(jumpPose);

         jumpElap += dt();
         if(jumpElap < 0.6) return;

         float toJump = jumpMod * 300 * dt();
         _pos += AVector3(0, toJump, 0);

         jumped += toJump;
         if(jumped >= jumpMax && jumpMod > 0)
         {
            jumpMod = -1;
         }else if(_pos[1] <= jumpedFrom && jumpElap > _jump.getDuration())
         {
            _jumping = false;
            walkElap = 0;
         }else if(_pos[1] <= jumpedFrom)
         {
            jumpMod = 0;
            _pos[1] = jumpedFrom;
         }
         return;
      }

      _pos += _forward * 100 * dt();

      APose pose = _walk.getValue(walkElap, true);
      walkElap += dt();

      pose.rootPos = _pos;
      pose.jointRots[0] = AQuaternion(AVector3(0,1,0), _heading) * pose.jointRots[0];
      //_skeleton.getRoot()->setLocalRotation(AQuaternion(AVector3(0,1,0), _heading));

      _skeleton.setPose(pose);

      _skeleton.fk();
   }

   virtual void keyPress(unsigned char key, int specialKey, int x, int y) 
   {
      if (key == 'd' || specialKey == GLUT_KEY_RIGHT)
      {
         _heading -= 0.05;
      }
      if (key == 'a' || specialKey == GLUT_KEY_LEFT)
      {
         _heading += 0.05;
      }

      if(key == 'm' && !_jumping)
      {
         _jumping = true;
         jumpedFrom = _pos[1];
         jumpMod = 1;
         jumpElap = 0;
      }
   }

protected:
   double _heading;

   AMotion _walk;
   AMotion _jump;
   ASkeleton _skeleton;
   ASkeletonDrawer _drawer;

   AVector3 _forward;
   AVector3 _pos;

   double walkElap;

   double jumpElap;
   float jumpedFrom;
   float jumped;
   float jumpMax;
   float jumpMod;
   bool _jumping;
};

int main(int argc, char** argv)
{
   WASDSimple viewer;
   viewer.init(argc, argv);
   viewer.run();
}

