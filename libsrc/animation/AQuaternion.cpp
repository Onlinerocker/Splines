#include "AQuaternion.h"
#include "AMatrix3.h"
#include "AVector3.h"
#include <algorithm>
#include <cmath>

using namespace std;

AQuaternion AQuaternion::Zero;
AQuaternion AQuaternion::Identity(0,0,0,1);

AQuaternion::AQuaternion()
{
    mW = 0; mX = 0; mY = 0; mZ = 0;
}

AQuaternion::AQuaternion(double x, double y, double z, double w)
{
    mW = w; mX = x; mY = y; mZ = z;
}

AQuaternion::AQuaternion(const AQuaternion& q)
{
    mW = q[VW]; mX = q[VX]; mY = q[VY]; mZ = q[VZ];
}

AQuaternion::AQuaternion(const AMatrix3& m)
{
	 fromMatrix(m);
}

AQuaternion::AQuaternion(const AVector3& axis, double rad)
{
	 fromAxisAngle(axis, rad);
}


double AQuaternion::Dot(const AQuaternion& q0, const AQuaternion& q1)
{
    return q0[VW] * q1[VW] + q0[VX] * q1[VX] + q0[VY] * q1[VY] + q0[VZ] * q1[VZ];
}

// Assignment operators
AQuaternion& AQuaternion::operator = (const AQuaternion& q)
{
    mW = q[VW]; mX = q[VX]; mY = q[VY]; mZ = q[VZ];
    return *this;
}

AQuaternion& AQuaternion::operator += (const AQuaternion& q)
{
    mW += q[VW]; mX += q[VX]; mY += q[VY]; mZ += q[VZ];
    return *this;
}

AQuaternion& AQuaternion::operator -= (const AQuaternion& q)
{
    mW -= q[VW]; mX -= q[VX]; mY -= q[VY]; mZ -= q[VZ];
    return *this;
}

AQuaternion& AQuaternion::operator *= (const AQuaternion& q)
{
    *this = AQuaternion(
        mW * q[VX] + mX * q[VW] + mY * q[VZ] - mZ * q[VY],
        mW * q[VY] + mY * q[VW] + mZ * q[VX] - mX * q[VZ],
        mW * q[VZ] + mZ * q[VW] + mX * q[VY] - mY * q[VX],
        mW * q[VW] - mX * q[VX] - mY * q[VY] - mZ * q[VZ]);
    return *this;
}

AQuaternion& AQuaternion::operator *= (double d)
{
    mW *= d; mX *= d; mY *= d; mZ *= d;
    return *this;
}

AQuaternion& AQuaternion::operator /= (double d)
{
    mW /= d; mX /= d; mY /= d; mZ /= d;
    return *this;
}

// Indexing
double& AQuaternion::operator [](int i)
{
    return mV[i];
}

double AQuaternion::operator [](int i) const
{
    return mV[i];
}

double AQuaternion::w() const
{
    return mW;
}

double AQuaternion::x() const
{
    return mX;
}

double AQuaternion::y() const
{
    return mY;
}

double AQuaternion::z() const
{
    return mZ;
}

// Friends

AQuaternion operator - (const AQuaternion& q)
{
    return AQuaternion(-q[VX], -q[VY], -q[VZ], -q[VW]); 
}

AQuaternion operator + (const AQuaternion& q0, const AQuaternion& q1)
{
    return AQuaternion(
			q0[VX] + q1[VX], 
			q0[VY] + q1[VY], 
			q0[VZ] + q1[VZ],
         q0[VW] + q1[VW]); 
}

AQuaternion operator - (const AQuaternion& q0, const AQuaternion& q1)
{
    return AQuaternion(
			q0[VX] - q1[VX], 
			q0[VY] - q1[VY], 
			q0[VZ] - q1[VZ],
			q0[VW] - q1[VW]); 
}

AQuaternion operator * (const AQuaternion& q, double d)
{
    return AQuaternion(
			q[VX] * d, 
			q[VY] * d, 
			q[VZ] * d,
			q[VW] * d); 
}

AVector3 operator * (const AQuaternion& q, const AVector3& v)
{
    AMatrix3 m = q.toMatrix();
    return m * v;
}

AQuaternion operator * (double d, const AQuaternion& q)
{
    return AQuaternion(
			q[VX] * d, 
			q[VY] * d, 
			q[VZ] * d,
			q[VW] * d); 
}

AQuaternion operator * (const AQuaternion& q0, const AQuaternion& q1)
{
    return AQuaternion(
        q0[VW] * q1[VX] + q0[VX] * q1[VW] + q0[VY] * q1[VZ] - q0[VZ] * q1[VY],
        q0[VW] * q1[VY] + q0[VY] * q1[VW] + q0[VZ] * q1[VX] - q0[VX] * q1[VZ],
        q0[VW] * q1[VZ] + q0[VZ] * q1[VW] + q0[VX] * q1[VY] - q0[VY] * q1[VX],
        q0[VW] * q1[VW] - q0[VX] * q1[VX] - q0[VY] * q1[VY] - q0[VZ] * q1[VZ]);
}

AQuaternion operator / (const AQuaternion& q, double d)
{
    return AQuaternion(
			q[VX] / d, 
			q[VY] / d, 
			q[VZ] / d,
			q[VW] / d);
}

bool operator == (const AQuaternion& q0, const AQuaternion& q1)
{
    float eps = 0.001f;
    // check q0 = q1 or q0 = -q1
    return (abs(q0[VW] - q1[VW]) < eps &&
            abs(q0[VX] - q1[VX]) < eps &&
            abs(q0[VY] - q1[VY]) < eps &&
            abs(q0[VZ] - q1[VZ]) < eps)
           ||
           (abs(q0[VW] + q1[VW]) < eps &&
            abs(q0[VX] + q1[VX]) < eps &&
            abs(q0[VY] + q1[VY]) < eps &&
            abs(q0[VZ] + q1[VZ]) < eps);
}

bool operator != (const AQuaternion& q0, const AQuaternion& q1)
{
    return !(q0 == q1); 
}

// special functions

double AQuaternion::sqrLength() const
{
    return mV[VW] * mV[VW] + mV[VX] * mV[VX] + mV[VY] * mV[VY] + mV[VZ] * mV[VZ];
}

double AQuaternion::length() const
{
    return sqrt(sqrLength());
}

AQuaternion AQuaternion::normalized() const
{
	 AQuaternion q = *this;
    double l = length();
    if (l > A_EPSILON)
    {
        q /= l;
    }
	 else
	 {
		  std::cout << "WARNING: Normalize AQuaternion with length 0\n";
	 }
	 return q;
}

void AQuaternion::normalize()
{
	 AQuaternion q = normalized();
    *this = q;
}

AQuaternion AQuaternion::inverse() const
{
    return AQuaternion(-mX, -mY, -mZ, mW) / sqrLength();
}

std::istream& operator >> (std::istream& s, AQuaternion& v)
{
    double x, y, z, w;
    s >> w >> x >> y >> z;
    v[VX] = x;
    v[VY] = y;
    v[VZ] = z;
    v[VW] = w;
    return s;
}

std::ostream& operator << (std::ostream& s, const AQuaternion& v)
{
    s << (float) v[VX] << " " 
      << (float) v[VY] << " " 
	   << (float) v[VZ] << " "
      << (float) v[VW];
    return s;
}
