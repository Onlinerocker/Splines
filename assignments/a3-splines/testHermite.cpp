#include <vector>
#include "AInterpolator.h"

#include <vector>
#include "AInterpolator.h"

int main()
{
   std::vector<AVector3> keys;
   keys.push_back(AVector3(0,0));
   keys.push_back(AVector3(1,2));
   keys.push_back(AVector3(3,3));
   keys.push_back(AVector3(6,3));
   keys.push_back(AVector3(8,0));

   AInterpolatorHermite hermite;
   hermite.resetControlPoints(keys);

   for (int i = 0; i <hermite.getNumControlPoints(); i++)
   {
       std::cout << hermite.getControlPoint(i) << std::endl;
   }
}

