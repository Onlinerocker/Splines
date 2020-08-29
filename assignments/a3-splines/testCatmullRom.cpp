#include "AInterpolator.h"
#include <vector>

int main()
{
   std::vector<AVector3> keys;
   keys.push_back(AVector3(0,0,0));
   keys.push_back(AVector3(1,1,0));
   keys.push_back(AVector3(2,0,0));

   AInterpolatorCatmullRom interp;
   interp.resetControlPoints(keys);

   // todo: print out keys and make sure they are correct
   for (int i = 0; i < interp.getNumControlPoints(); i++)
   {
       std::cout << "PTS: " << std::endl;
       std::cout << interp.getControlPoint(i) << std::endl;
   }
}

