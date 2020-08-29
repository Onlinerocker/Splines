#ifndef aConstants_H_
#define aConstants_H_

const double M_PI = 3.1415926535897932384626433832795;
const double A_PI = 3.1415926535897932384626433832795;
const double A_PI_2 = 1.5707963267948966192313216916398;
const double M_PI_2 = 1.5707963267948966192313216916398;
const double A_EPSILON = 0.000001;
const double ARad2Deg = (180.0f / A_PI);			// Rad to Degree
const double ADeg2Rad = (A_PI / 180.0f);			// Degree to Rad

template <typename T>
bool IS_ZERO(T x, double eps = 0.001) 
{
	return abs(x) < eps;
}

template <typename T>
int SGN(T x)
{
	return (x >= 0? 1: -1); 
}

enum {VX, VY, VZ, VW};

#endif

