#include "AMatrix3.h"
#include "AQuaternion.h"
#include <algorithm>
#include <string.h>
#include <cmath>

using namespace std;

AMatrix3 AMatrix3::Zero;
AMatrix3 AMatrix3::Identity(1,0,0, 0,1,0, 0,0,1);

AMatrix3::AMatrix3() 
{
	 memset(mM, 0, sizeof(double)*9);
}

AMatrix3::AMatrix3(double a11, double a12, double a13,
                   double a21, double a22, double a23,
                   double a31, double a32, double a33)
{
	 m11 = a11; m12 = a12; m13 = a13;
	 m21 = a21; m22 = a22; m23 = a23;
	 m31 = a31; m32 = a32; m33 = a33;
}

AMatrix3::AMatrix3(const AMatrix3& m)
{ 
	 memcpy(mM, m.mM, sizeof(double)*9);
}

AMatrix3::AMatrix3(const AQuaternion& q)
{ 
	 fromQuaternion(q);
}

AMatrix3::AMatrix3(AMatrix3::RotOrder roo, const AVector3& eulerAngles)
{
	 fromEulerAngles(roo, eulerAngles);
}

AMatrix3::AMatrix3(const AVector3& axis, double rad)
{
	 fromAxisAngle(axis, rad);
}

AVector3 AMatrix3::toEulerAngles(AMatrix3::RotOrder roo) const
{
	 switch (roo)
	 {
	 case XYZ: return toEulerAnglesXYZ(); 
	 case XZY: return toEulerAnglesXZY(); 
	 case YXZ: return toEulerAnglesYXZ(); 
	 case YZX: return toEulerAnglesYZX(); 
	 case ZXY: return toEulerAnglesZXY(); 
	 case ZYX: return toEulerAnglesZYX(); 
	 }
	 return AVector3();
}

void AMatrix3::fromEulerAngles(AMatrix3::RotOrder roo, const AVector3& eulerAngles)
{
	 switch (roo)
	 {
	 case XYZ: fromEulerAnglesXYZ(eulerAngles); break;
	 case XZY: fromEulerAnglesXZY(eulerAngles); break;
	 case YXZ: fromEulerAnglesYXZ(eulerAngles); break;
	 case YZX: fromEulerAnglesYZX(eulerAngles); break;
	 case ZXY: fromEulerAnglesZXY(eulerAngles); break;
	 case ZYX: fromEulerAnglesZYX(eulerAngles); break;
	 }
}

// Conversion with Quaternion
AQuaternion AMatrix3::toQuaternion() const
{
    AQuaternion q;
    q.fromMatrix(*this);
    return q;
}

void AMatrix3::fromQuaternion(const AQuaternion& q) 
{
    *this = q.toMatrix();
}

// ASSIGNMENT OPERATORS
AMatrix3& AMatrix3::operator = ( const AMatrix3& m )
{ 
    for (size_t i = 0; i < 3; i++)
	 	 for (size_t j = 0; j < 3; j++) 
		 	   mM[i][j] = m[i][j]; 
    return *this; 
}

AMatrix3& AMatrix3::operator += ( const AMatrix3& m )
{ 
    for (size_t i = 0; i < 3; i++)
	 	 for (size_t j = 0; j < 3; j++) 
		 	   mM[i][j] += m[i][j]; 
    return *this; 
}

AMatrix3& AMatrix3::operator -= ( const AMatrix3& m )
{ 
    for (size_t i = 0; i < 3; i++)
	 	 for (size_t j = 0; j < 3; j++) 
		 	   mM[i][j] -= m[i][j]; 
    return *this; 
}

AMatrix3& AMatrix3::operator *= ( double d )
{ 
    for (size_t i = 0; i < 3; i++)
	 	 for (size_t j = 0; j < 3; j++) 
		 	   mM[i][j] *= d; 
    return *this; 
}

AMatrix3& AMatrix3::operator /= ( double d )
{ 
    for (size_t i = 0; i < 3; i++)
	 	 for (size_t j = 0; j < 3; j++) 
		 	   mM[i][j] /= d; 
    return *this; 
}

double* AMatrix3::operator [] (int i) 
{
    assert(! (i < 0 || i > 3));
    return mM[i];
}

const double* AMatrix3::operator [] (int i) const 
{
    assert(!(i < 0 || i > 3));
    return mM[i];
}

// SPECIAL FUNCTIONS

AMatrix3 AMatrix3::transpose() const 
{
    return AMatrix3(
        mM[0][0], mM[1][0], mM[2][0],
        mM[0][1], mM[1][1], mM[2][1],
        mM[0][2], mM[1][2], mM[2][2]);
}

// FRIENDS
AMatrix3 operator - (const AMatrix3& a)
{ 
    return AMatrix3(-a.m11, -a.m12, -a.m13, 
                    -a.m21, -a.m22, -a.m23,
                    -a.m31, -a.m32, -a.m33);
}

AMatrix3 operator + (const AMatrix3& a, const AMatrix3& b)
{ 
	 AMatrix3 result;
	 for (size_t i = 0; i < 3; i++)
	 	 for (size_t j = 0; j < 3; j++)
	 	 	  result[i][j] = a[i][j] + b[i][j];
	 return result;
}

AMatrix3 operator - (const AMatrix3& a, const AMatrix3& b)
{ 
	 AMatrix3 result;
	 for (size_t i = 0; i < 3; i++)
	 	 for (size_t j = 0; j < 3; j++)
	 	 	  result[i][j] = a[i][j] - b[i][j];
	 return result;
}

AMatrix3 operator * (const AMatrix3& a, const AMatrix3& b)
{
#define ROWCOL(i, j) \
    (a[i][0]*b[0][j] + a[i][1]*b[1][j] + a[i][2]*b[2][j])
    return AMatrix3(ROWCOL(0,0), ROWCOL(0,1), ROWCOL(0,2),
                    ROWCOL(1,0), ROWCOL(1,1), ROWCOL(1,2),
                    ROWCOL(2,0), ROWCOL(2,1), ROWCOL(2,2));
#undef ROWCOL // (i, j)
}

AMatrix3 operator * (const AMatrix3& a, double d)
{ 
	 AMatrix3 result;
	 for (size_t i = 0; i < 3; i++)
	 	 for (size_t j = 0; j < 3; j++)
	 	 	  result[i][j] = d * a[i][j];
	 return result;
}

AMatrix3 operator * (double d, const AMatrix3& a)
{ 
    return a*d; 
}

AMatrix3 operator / (const AMatrix3& a, double d)
{ 
	 AMatrix3 result;
	 for (size_t i = 0; i < 3; i++)
	 	 for (size_t j = 0; j < 3; j++)
	 	 	  result[i][j] = a[i][j] / d;
	 return result;
}

int operator == (const AMatrix3& a, const AMatrix3& b)
{ 
	 double eps = 0.001; // very lenient tolerance
	 for (size_t i = 0; i < 3; i++)
	 	 for (size_t j = 0; j < 3; j++)
	 	 	  if (abs(a[i][j] - b[i][j]) > eps)
				   return 0;
	 return 1;
}

int operator != (const AMatrix3& a, const AMatrix3& b)
{ 
    return !(a == b); 
}

std::istream& operator >> (std::istream& s, AMatrix3& v)
{
    double value;
    for (unsigned int i = 0; i < 3; i++)
        for (unsigned int j = 0; j < 3; j++)
        {
            s >> value;
            v[i][j] = value;
        }
    return s;
}

std::ostream& operator << (std::ostream& s, const AMatrix3& v)
{
    for (unsigned int i = 0; i < 3; i++)
    {
        for (unsigned int j = 0; j < 2; j++)
        {
            s << (float) v[i][j] << " ";
        }
        s << (float) v[i][2] << std::endl;
    }
    return s;
}


AVector3 operator * (const AMatrix3& a, const AVector3& v)
{
#define ROWCOL(i) \
    (a[i][0]*v[0] + a[i][1]*v[1] + a[i][2]*v[2])
    return AVector3(ROWCOL(0), ROWCOL(1), ROWCOL(2));
#undef ROWCOL // (i)
}

void AMatrix3::writeToGLMatrix(float* m) const
{
    m[0] = mM[0][0]; m[4] = mM[0][1]; m[8] = mM[0][2];  m[12] = 0.0f;
    m[1] = mM[1][0]; m[5] = mM[1][1]; m[9] = mM[1][2];  m[13] = 0.0f;
    m[2] = mM[2][0]; m[6] = mM[2][1]; m[10] = mM[2][2]; m[14] = 0.0f;
    m[3] = 0.0f;    m[7] = 0.0f;    m[11] = 0.0f;    m[15] = 1.0f;
}

