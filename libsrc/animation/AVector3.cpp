#include "AVector3.h"
#include <algorithm>
#include <cmath>

const AVector3 AVector3::AxisX(1.0f, 0.0f, 0.0f);
const AVector3 AVector3::AxisY(0.0f, 1.0f, 0.0f);
const AVector3 AVector3::AxisZ(0.0f, 0.0f, 1.0f);
const AVector3 AVector3::Zero(0.0f, 0.0f, 0.0f);

using namespace std;

AVector3::AVector3() 
{
    mX = 0; mY = 0; mZ = 0; 
}

AVector3::AVector3(double x, double y, double z)
{ 
    mX = x; mY = y; mZ = z; 
}

AVector3::AVector3(const AVector3& v)
{ 
    mX = v[VX]; mY = v[VY]; mZ = v[VZ]; 
}

// ASSIGNMENT OPERATORS

AVector3& AVector3::operator = (const AVector3& v)
{ 
    mV[VX] = v[VX]; mV[VY] = v[VY]; mV[VZ] = v[VZ]; return *this; 
}

AVector3& AVector3::operator += ( const AVector3& v )
{ 
    mV[VX] += v[VX]; mV[VY] += v[VY]; mV[VZ] += v[VZ]; return *this; 
}

AVector3& AVector3::operator -= ( const AVector3& v )
{ 
    mV[VX] -= v[VX]; mV[VY] -= v[VY]; mV[VZ] -= v[VZ]; return *this; 
}

AVector3& AVector3::operator *= ( double d )
{ 
    mV[VX] *= d; mV[VY] *= d; mV[VZ] *= d; return *this; 
}

AVector3& AVector3::operator /= ( double d )
{ 
    double d_inv = 1.0f/d; 
    mV[VX] *= d_inv; mV[VY] *= d_inv; mV[VZ] *= d_inv;
    return *this; 
}

double& AVector3::operator [] ( int i) {
    assert(! (i < VX || i > VZ));
    return mV[i];
}

double AVector3::operator [] ( int i) const {
    assert(! (i < VX || i > VZ));
    return mV[i];
}

double AVector3::x() const
{
	return mX;
}

double AVector3::y() const
{
	return mY;
}

double AVector3::z() const
{
	return mZ;
}

// SPECIAL FUNCTIONS
double AVector3::length() const
{  
    return sqrt(sqrLength()); 
}

double AVector3::sqrLength() const
{  
    return mV[VX]*mV[VX] + mV[VY]*mV[VY] + mV[VZ]*mV[VZ]; 
}

AVector3 AVector3::normalized() const 
{
    double len = length();
	 AVector3 copy = *this;
    if (len > A_EPSILON) copy /= length(); 
    return copy;
}

void AVector3::normalize() 
{ 
    *this = normalized();
}

AVector3 AVector3::Cross(const AVector3 &left, const AVector3& right)
{
	 double x = left.y() * right.z() - left.z() * right.y();
	 double y = left.z() * right.x() - left.x() * right.z();
	 double z = left.x() * right.y() - left.y() * right.x();
    return AVector3(x,y,z);
}

// FRIENDS
AVector3 operator - (const AVector3& a)
{  
    return AVector3(-a.x() ,-a.y(),-a.z()); 
}

AVector3 operator + (const AVector3& a, const AVector3& b)
{ 
    return AVector3(a.x() + b.x(), a.y() + b.y(), a.z() + b.z()); 
}

AVector3 operator - (const AVector3& a, const AVector3& b)
{ 
    return AVector3(a.x() - b.x(), a.y() - b.y(), a.z() - b.z()); 
}

AVector3 operator * (const AVector3& a, double d)
{ 
    return AVector3(d*a.x(), d*a.y(), d*a.z()); 
}

AVector3 operator * (double d, const AVector3& a)
{ 
    return a*d; 
}

double operator * (const AVector3& a, const AVector3& b)
{ 
    return (a.x()*b.x() + a.y()*b.y() + a.z()*b.z()); 
}

AVector3 operator / (const AVector3& a, double d)
{ 
    double d_inv = 1.0/d; 
    return AVector3(a.x()*d_inv, a.y()*d_inv, a.z()*d_inv); 
}


int operator == (const AVector3& a, const AVector3& b)
{ 
    float eps = 0.001f; // low precision equality
    return (fabs(a.x() - b.x()) < eps && 
            fabs(a.y() - b.y()) < eps && 
            fabs(a.z() - b.z()) < eps);
}

int operator != (const AVector3& a, const AVector3& b)
{ 
    return !(a == b); 
}

double AVector3::Dot(const AVector3& a, const AVector3& b)
{
    return a[VX]*b[VX] + a[VY]*b[VY] + a[VZ]*b[VZ];
}

std::istream& operator>>(std::istream& s, AVector3& v)
{
    double x, y, z;
    s >> x >> y >> z;
    v = AVector3(x, y, z);
    return s;
}

std::ostream& operator<<(std::ostream& s, const AVector3& v)
{
    s << (float) v[VX] << " " << (float) v[VY] << " " << (float) v[VZ];
    return s;
}

AVector3 AVector3::Lerp(const AVector3& a, const AVector3& b, float t)
{
    return a * (1-t) + b * t;
}

double AVector3::Distance(const AVector3& a, const AVector3& b)
{
    return sqrt(DistanceSqr(a,b));
}

double AVector3::DistanceSqr(const AVector3& a, const AVector3& b)
{
    return (a[0]-b[0])*(a[0]-b[0]) + 
           (a[1]-b[1])*(a[1]-b[1]) + 
           (a[2]-b[2])*(a[2]-b[2]);
}
