#ifndef AInterpolatorBasecode_H_
#define AInterpolatorBasecode_H_

#include <string>
#include <vector>
#include <Eigen/Dense>
#include "AInterpolator.h"
#include <math.h>

//---------------------------------------
// Linear
//---------------------------------------
AVector3 AInterpolatorLinear::interpolate(int segment, double u) const
{
   //Getting the first and second control points
   AVector3 start = getControlPoint(segment, 0);
   AVector3 end = getControlPoint(segment, 1);

   //Linearly interpolate between control points 'start' and 'end'
   AVector3 pos = (1-u) * start + u * end;

   return pos;
}

void AInterpolatorLinear::computeControlPoints(const std::vector<AVector3>& keys)
{
   AVector3 p0, p1;

   //Set the control points for every segment
   for(int x=0; x<keys.size() - 1; x++)
   {
      p0 = keys[x];
      p1 = keys[x+1];

      int segment = x;
      setControlPoint(segment, 0, p0);
      setControlPoint(segment, 1, p1);
   }

}

//---------------------------------------
// Catmull-Rom 
//---------------------------------------

//Calculates the control points for a Catmull-Rom spline.
void AInterpolatorCatmullRom::computeControlPoints(
    const std::vector<AVector3>& keys)
{
   AVector3 p0, p1, p2, p3;

   //Special case for first segement...
   //we can't use the previous segements start point
   //in our calculations, so we use keys[0]
   p0 = keys[0];
   p1 = keys[0] + ( (1.0/6.0) * (keys[1] - keys[0]) );

   if(keys.size() <= 2)
      p2 = keys[1] - ( (1.0/6.0) * (keys[1] - keys[0]) );
   else
      p2 = keys[1] - ( (1.0/6.0) * (keys[2] - keys[0]) );
   
   p3 = keys[1];

   int segment = 0;
   setControlPoint(segment, 0, p0);
   setControlPoint(segment, 1, p1);
   setControlPoint(segment, 2, p2);
   setControlPoint(segment, 3, p3);

   //Calculate control points for all segements after the first
   int x = 1;
   for(x=1; x<=keys.size() - 2; x++)
   {
      p0 = keys[x];
      p1 = keys[x] + ( (1.0/6.0) * (keys[x+1] - keys[x-1]) );
      if(x == keys.size()-2)
         p2 = keys[x+1] - ( (1.0/6.0) * (keys[x+1] - keys[x]) );
      else
         p2 = keys[x+1] - ( (1.0/6.0) * (keys[x+2] - keys[x]) );
      p3 = keys[x+1];

      segment = x;
      setControlPoint(segment, 0, p0);
      setControlPoint(segment, 1, p1);
      setControlPoint(segment, 2, p2);
      setControlPoint(segment, 3, p3);
   }

}

//Simple linear interpolation between 'pos' and 'pos1'
AVector3 myLerp(AVector3 pos, AVector3 pos1, double t){
    return (1.0 - t) * pos + (t*pos1);
}

AVector3 AInterpolatorCatmullRom::interpolate(int segment, double t) const
{
   //Grab the four control points for the given segmenti
   AVector3 b0 = getControlPoint(segment, 0);
   AVector3 b1 = getControlPoint(segment, 1);
   AVector3 b2 = getControlPoint(segment, 2);
   AVector3 b3 = getControlPoint(segment, 3);

   //Calculate prime values using linear interpolation
   AVector3 b0Prime = myLerp(b0, b1, t);
   AVector3 b1Prime = myLerp(b1, b2, t);
   AVector3 b2Prime = myLerp(b2, b3, t);

   AVector3 b0Prime1 = myLerp(b0Prime, b1Prime, t);
   AVector3 b1Prime1 = myLerp(b1Prime, b2Prime, t);

   //Calculate final location by lerping 'b0Prime1' and 'b1Prime1'
   AVector3 ans = myLerp(b0Prime1, b1Prime1, t);

   return ans;
}

//---------------------------------------
// Hermite
//---------------------------------------
AVector3 AInterpolatorHermite::interpolate(int segment, double t) const
{
   
   AVector3 b0 = getControlPoint(segment, 0); //Get starting point
   AVector3 b1 = getControlPoint(segment, 1); //Get starting tangent

   AVector3 b2 = getControlPoint(segment, 2); //Get ending point
   AVector3 b3 = getControlPoint(segment, 3); //Get ending tangent

   AVector3 ans;

   //If we're at time zero, we know we are at the first control point (b0)
   if(t == 0)
      return b0;

   //If we're at time one, we know we are at the third control point (b2)
   if(t == 1)
      return b2;
   
   //Calculate the interpolated point using the cubic Hermite spline
   //equation. 
   //https://end.wikipedia.org/wiki/Cubic_Hermite_spline
   double term = 1 - 3*pow(t,2) + 2*pow(t,3);
   double term1 = t - 2*pow(t,2) + pow(t,3);
   double term2 = -1 * pow(t,2) + pow(t,3);
   double term3 = 3*pow(t,2) - 2 * pow(t,3);

   ans = (term * b0) + (term1 * b1)  + (term2 * b3) + (term3 * b2);
   
   return ans;
}


void AInterpolatorHermite::computeControlPoints(
    const std::vector<AVector3>& keys)
{
   Eigen::MatrixXd A = Eigen::MatrixXd::Zero(keys.size(), keys.size()); //Matrix containing coefficients
   Eigen::MatrixXd P = Eigen::MatrixXd::Zero(keys.size(), 2); //Matrix containing Px (points the spline passes through)
   Eigen::MatrixXd P1(keys.size(),2); //Matrix containing Px_Prime

   //...where P = A * P1

   int *vals = new int[3];
   vals[0] = 1;
   vals[1] = 4;
   vals[2] = 1;

   A(0,0) = 2; 
   A(0, 1) = 1;
   A(keys.size() - 1, keys.size() - 2) = 1; 
   A(keys.size() - 1, keys.size() - 1) = 2;

   AVector3 P_0 = 3 * (keys[1] - keys[0]);
   AVector3 P_N = 3 * (keys[keys.size() - 1] - keys[keys.size() - 2]);

   P(0,0) = P_0.x(); 
   P(0,1) = P_0.y();

   P(keys.size() - 1,0) = P_N.x(); 
   P(keys.size() - 1,1) = P_N.y();

   if(keys.size() > 2){
      int x=1;

      for(x=1; x<keys.size()-1; x++){
         AVector3 P_X = 3 * (keys[x+1] - keys[x-1]);
         P(x,0) = P_X.x();
         P(x,1) = P_X.y();

         for(int y=0; y<3; y++){
            A(x,(x-1) + y) = vals[y];
         }
      }  
   }

   //Since P = A * P1, we can solve for P1
   //by multiplying P by the inverse of A
   P1 = A.inverse() * P;

   //P1 now contains the values for each Px_Prime ( x = [0, keys.size()-1] )
   //We can now set the control points for each segment
   for(int ind=0; ind<keys.size() - 1; ind++){
      AVector3 b1 = AVector3(P1(ind, 0), P1(ind, 1), keys[ind].z());
      AVector3 b3 = AVector3(P1(ind+1, 0), P1(ind+1, 1), keys[ind].z());

      setControlPoint(ind, 0, keys[ind]);
      setControlPoint(ind, 1, b1);
      setControlPoint(ind, 2, keys[ind+1]);
      setControlPoint(ind, 3, b3);
   }

   delete vals;
}

#endif

