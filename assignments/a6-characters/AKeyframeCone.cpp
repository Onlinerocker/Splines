#include "AFramework.h"
#include "AnimationToolkit.h"
#include "AGLObjects.h"

class AKeyframeCone : public AFramework
{
public:
   AKeyframeCone() : AFramework(AFramework::Perspective)
   {
   }

   virtual ~AKeyframeCone() 
   {
   }

   virtual void setup()
   {
      AQuaternion q0, q1, q2, q3;
      q0.fromAxisAngle(AVector3(0,1,0), 90 * ADeg2Rad);
      q1.fromAxisAngle(AVector3(0,1,0), 180 * ADeg2Rad);
      q2.fromAxisAngle(AVector3(0,1,0), 270 * ADeg2Rad);
      q3.fromAxisAngle(AVector3(0,1,0), 360 * ADeg2Rad);

      mOri.appendKey(0, q3);
      mOri.appendKey(1, q2);
      mOri.appendKey(3, q2);
      mOri.appendKey(4, q1);
      mOri.appendKey(6, q1);
      mOri.appendKey(7, q0);
      mOri.appendKey(9, q0);
      mOri.appendKey(10, q3);
      mOri.appendKey(12, q3);

      AVector3 p0, p1, p2, p3;
      p0 = AVector3(100,0,100);
      p1 = AVector3(-100,0,100);
      p2 = AVector3(-100,0,-100);
      p3 = AVector3(100,0,-100);

      mPos.appendKey(0, p0);
      mPos.appendKey(1, p0);

      mPos.appendKey(3, p1);
      mPos.appendKey(4, p1);

      mPos.appendKey(6, p2);
      mPos.appendKey(7, p2);

      mPos.appendKey(9, p3);
      mPos.appendKey(10, p3);

      mPos.appendKey(12, p0);

   }

   virtual void draw()
   {
      ASetMaterial(AVector3(1,0,0));

      AVector3 pos = mPos.getValue(elapsedTime(), true);
      AQuaternion quat = mOri.getValue(elapsedTime(), true);

      ADrawCone(pos, AMatrix3(quat), AVector3(10,10,20));
   }

protected:
   AQuatSpline mOri;
   ASpline mPos;
};

int main(int argc, char** argv)
{
   AKeyframeCone viewer;
   viewer.init(argc, argv);
   viewer.run();
}

