#include "AFramework.h"
#include "AnimationToolkit.h"
#include "AGLObjects.h"

class AStackingBoxes : public AFramework
{
public:
   AStackingBoxes() : AFramework(AFramework::Perspective) {}
   virtual ~AStackingBoxes() {}

   void draw()
   {
      // Question 1 - B1
      ATransform F0_1; // transform from frame 1 to world
      F0_1.translation = AVector3(-2,0,1);
      F0_1.rotation = AQuaternion::Identity; 
      ASetMaterial(AVector3(0,0.5,0));
      drawBox(F0_1);

      // Question 1 - B2
      ATransform F0_2; // transform from frame 2 to world
      F0_2.translation = AVector3(4,0,2);
      
      AQuaternion q2(AVector3(0,0,1), 45 * ADeg2Rad);
      
      F0_2.rotation = q2; 
      ASetMaterial(AVector3(0.5,0, 0.5));
      drawBox(F0_2);

      // Question 1 - B3
      ATransform F0_3; // transform from frame 3 to world
      F0_3.translation = AVector3(5,4,2);

      AQuaternion q3(AVector3(0,0,1), 90 * ADeg2Rad);

      F0_3.rotation = q3;
      ASetMaterial(AVector3(0.0, 0.5,0.5));
      drawBox(F0_3);

      // Question 2
      ATransform F1_2 = F0_1.inverse() * F0_2;
      AVector3 value = F1_2.transformPoint(AVector3(0,0,0));
      std::cout << "Position of b2 relative to b1 is " << value << std::endl;

      // Question 3
      ATransform F2_3 = F0_2.inverse() * F0_3;
      value = F2_3.transformPoint(AVector3(0,0,0));
      std::cout << "Position of b3 relative to b2 is " << value << std::endl;

      // Question 4
      ATransform F_OFFSET;
      F_OFFSET.rotation = AQuaternion::Identity;
      F_OFFSET.translation = AVector3(0,2,0);
      ATransform F = F_OFFSET * F0_1 * F0_2.inverse();

      ASetMaterial(AVector3(0.5, 0.5,0.5));
      drawBox(F * F0_2);
   }

   void drawBox(const ATransform& xform)
   {
      AVector3 size(30, 20, 10);
      AVector3 halfSize = 0.5 * size;
      AVector3 pos = 10 * xform.translation;
      glPushMatrix();
      glTranslatef(pos[0], pos[1], pos[2]);
      ASetRotation(xform.rotation.toMatrix());
      glTranslatef(halfSize[0], halfSize[1], -halfSize[2]);
      glScalef(size[0], size[1], size[2]);
      glutSolidCube(1.0);
      glPopMatrix();

      glDisable(GL_LIGHTING);
      ASetColor(AVector3(1,0,0));
      ADrawLine(pos, pos + xform.transformVector(AVector3(10,0,0)));

      ASetColor(AVector3(0,1,0));
      ADrawLine(pos, pos + xform.transformVector(AVector3(0,10,0)));

      ASetColor(AVector3(0,0,1));
      ADrawLine(pos, pos + xform.transformVector(AVector3(0,0,10)));
      glEnable(GL_LIGHTING);
   }
};

int main(int argc, char** argv)
{
   AStackingBoxes viewer;
   viewer.init(argc, argv);
   viewer.run();
   return 0;
}
