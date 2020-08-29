#include <iostream>
#include "AnimationToolkit.h"

int main(int argc, char** argv)
{
   AQuaternion q(AVector3(0,0,1), 0 * ADeg2Rad);

   AQuaternion q45(AVector3(0,0,0), 45 * ADeg2Rad);

   ATransform t1(q, AVector3(1,2,0));
   std::cout << "T1 " << t1 << std::endl;

   ATransform t2(q45, AVector3(2,7,0));
   std::cout << "T2 " << t2 << std::endl;

   ATransform t2Inv = t2.inverse(); 
   std::cout << "T2 inverse " << t2Inv << std::endl;

   ATransform t = t1 * t2; 
   std::cout << "T1 * T2 " << t << std::endl;


   ATransform t3 = t2 * t2Inv;
   std::cout << t2Inv.rotation.toMatrix() << std::endl;
   std::cout << t3.rotation.toMatrix() << std::endl;
   std::cout << t3.translation << std::endl;
   std::cout << "T2 * T2_INV " << t3 << std::endl;
}

