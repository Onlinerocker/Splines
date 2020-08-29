#include <iostream>
#include "AnimationToolkit.h"

int main(int argc, char** argv)
{
   AQuaternion q0(AVector3(0,0,1), 0 * ADeg2Rad);
   AQuaternion q1(AVector3(0,0,1), 120 * ADeg2Rad);

   AQuaternion q = AQuaternion::Slerp(q0, q1, 0.5);
   std::cout << q << std::endl;
}

