#include "AMatrix3.h"
#include "AQuaternion.h"
#include <math.h>

AMatrix3 getRx(double rotX)
{
   AMatrix3 rx = AMatrix3();

   rx[0][0] = 1; rx[0][1] = 0; rx[0][2] = 0;
   rx[1][0] = 0; rx[1][1] = cos(rotX); rx[1][2] = -1 * sin(rotX);
   rx[2][0] = 0; rx[2][1] = sin(rotX); rx[2][2] = cos(rotX);

   return rx;
}

AMatrix3 getRy(double rotY)
{
   AMatrix3 ry = AMatrix3();

   ry[0][0] = cos(rotY); ry[0][1] = 0; ry[0][2] = sin(rotY);
   ry[1][0] = 0; ry[1][1] = 1; ry[1][2] = 0;
   ry[2][0] = -1 * sin(rotY); ry[2][1] = 0; ry[2][2] = cos(rotY);

   return ry;
}

AMatrix3 getRz(double rotZ)
{
   AMatrix3 rz = AMatrix3();

   rz[0][0] = cos(rotZ); rz[0][1] = -1 * sin(rotZ); rz[0][2] = 0;
   rz[1][0] = sin(rotZ); rz[1][1] = cos(rotZ); rz[1][2] = 0;
   rz[2][0] = 0; rz[2][1] = 0; rz[2][2] = 1;

   return rz;
}

AVector3 AMatrix3::toEulerAnglesXYZ() const
{
   AVector3 ans = AVector3(0,0,0);

   ans[1] = asin(mM[0][2]);

   if(std::abs( (ans[1] * ARad2Deg) - 90) < A_EPSILON){
      ans[0] = atan2(mM[1][0], mM[1][1]);
      ans[2] = 0;
   }else if(std::abs( (ans[1] * ARad2Deg) - (-90)) < A_EPSILON){
      ans[2] = atan2(mM[1][0], mM[1][1]);
      ans[0] = 0;
   }else{
      ans[0] = atan2(-1 * mM[1][2], mM[2][2]);
      ans[2] = atan2(-1 * mM[0][1], mM[0][0]);
   }

   return ans;
}

AVector3 AMatrix3::toEulerAnglesXZY() const
{
   AVector3 ans = AVector3(0,0,0);

   ans[2] = asin(-1 * mM[0][1]);

   if(std::abs( (ans[2] * ARad2Deg) - 90) < A_EPSILON){
      ans[0] = atan2(-1 * mM[1][2], mM[2][2]);
      ans[1] = 0;
   }else if(std::abs( (ans[2] * ARad2Deg) - (-90)) < A_EPSILON){
      ans[0] = atan2(-1 * mM[1][2], mM[2][2]);
      ans[1] = 0;
   }else{
      ans[0] = atan2(mM[2][1], mM[1][1]);
      ans[1] = atan2(mM[0][2], mM[0][0]);
   }

   return ans;
}

AVector3 AMatrix3::toEulerAnglesYXZ() const
{
   AVector3 ans = AVector3(0,0,0);

   ans[0] = asin(mM[1][2] * -1);

   if(std::abs( (ans[0] * ARad2Deg) - 90) < A_EPSILON){
      ans[1] = atan2(mM[0][1], mM[0][0]);
      ans[2] = 0;
   }else if(std::abs( (ans[0] * ARad2Deg) - (-90)) < A_EPSILON){
      ans[1] = atan2(-1 * mM[0][1], mM[0][0]);
      ans[2] = 0;
   }else{
      ans[1] = atan2(mM[0][2], mM[2][2]);
      ans[2] = atan2(mM[1][0], mM[1][1]);
   }

   return ans;
}

AVector3 AMatrix3::toEulerAnglesYZX() const
{
   AVector3 ans = AVector3(0,0,0);

   ans[2] = asin(mM[1][0]);

   if(std::abs( (ans[2] * ARad2Deg) - 90) < A_EPSILON){
      ans[0] = atan2(mM[0][2], mM[2][2]);
      ans[1] = 0;
   }else if(std::abs( (ans[2] * ARad2Deg) - (-90)) < A_EPSILON){
      ans[1] = atan2(mM[0][2], mM[0][1]);
      ans[0] = 0;
   }else{
      ans[0] = atan2(-1 * mM[1][2], mM[1][1]);
      ans[1] = atan2(-1 * mM[2][0], mM[0][0]);
   }

   return ans;
}

AVector3 AMatrix3::toEulerAnglesZXY() const
{
   AVector3 ans = AVector3(0,0,0);

   ans[0] = asin(mM[2][1]);

   if(std::abs( (ans[1] * ARad2Deg) - 90) < A_EPSILON){
      ans[1] = atan2(mM[1][0], mM[0][0]);
      ans[2] = 0;
   }else if(std::abs( (ans[1] * ARad2Deg) - (-90)) < A_EPSILON)
   {
      ans[1] = atan2(mM[0][2], mM[1][2]);
      ans[2] = 0;
   }
   else{
      ans[1] = atan2(-1 * mM[2][0], mM[2][2]);
      ans[2] = atan2(-1 * mM[0][1], mM[1][1]);
   }

   return ans;
}

AVector3 AMatrix3::toEulerAnglesZYX() const
{
   AVector3 ans = AVector3(0,0,0);

   ans[1] = asin(mM[2][0] * -1);

   if(std::abs( (ans[1] * ARad2Deg) - 90) < A_EPSILON){
      ans[0] = atan2(mM[0][1], mM[0][2]);
      ans[2] = 0;
   }else{
      ans[0] = atan2(mM[2][1], mM[2][2]);
      ans[2] = atan2(mM[1][0], mM[0][0]);
   }

   return ans;
}

void AMatrix3::fromEulerAnglesXYZ(const AVector3& angleRad)
{
   *this = Identity;
   *this = getRx(angleRad[0]) * getRy(angleRad[1]) * getRz(angleRad[2]);
}

void AMatrix3::fromEulerAnglesXZY(const AVector3& angleRad)
{
   *this = Identity;
   *this = getRx(angleRad[0]) * getRz(angleRad[2]) * getRy(angleRad[1]);
}

void AMatrix3::fromEulerAnglesYXZ(const AVector3& angleRad)
{
   *this = Identity;
   *this = getRy(angleRad[1]) * getRx(angleRad[0]) * getRz(angleRad[2]);
}

void AMatrix3::fromEulerAnglesYZX(const AVector3& angleRad)
{
   *this = Identity;
   *this = getRy(angleRad[1]) * getRz(angleRad[2]) * getRx(angleRad[0]);
}

void AMatrix3::fromEulerAnglesZXY(const AVector3& angleRad)
{
   *this = Identity;
   *this = getRz(angleRad[2]) * getRx(angleRad[0]) * getRy(angleRad[1]);
}

//TO DO
void AMatrix3::fromEulerAnglesZYX(const AVector3& angleRad)
{
   *this = Identity;
   *this = getRz(angleRad[2]) * getRy(angleRad[1]) * getRx(angleRad[0]);
}

void AMatrix3::toAxisAngle(AVector3& axis, double& angleRad) const
{
   // TODO
}

void AMatrix3::fromAxisAngle(const AVector3& axis, double angleRad)
{
   // TODO
   *this = Identity;
}



