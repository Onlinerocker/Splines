// alinen 2017
//
#ifndef aVector_H_
#define aVector_H_

#include <iostream>
#include <assert.h>
#include "AConstants.h"

class AVector3
{
public:
    // Constructors
    AVector3();
    AVector3(double x, double y, double z = 0);
    AVector3(const AVector3& v);			

    // Assignment operators
    AVector3& operator = ( const AVector3& v );	
    AVector3& operator += ( const AVector3& v );
    AVector3& operator -= ( const AVector3& v );
    AVector3& operator *= ( double d );	
    AVector3& operator /= ( double d );

    double& operator [] ( int i);
    double operator[] (int i) const;
    double x() const;
    double y() const;
    double z() const;

    // special functions
    double length() const;				// length of a Vector3
    double sqrLength() const;		   // squared length of a Vector3
    void normalize();					// normalize a Vector3 in place
    AVector3 normalized() const;	   // Returns this vector with length 1

    // friends
    friend  AVector3 operator - (const AVector3& v);
    friend  AVector3 operator + (const AVector3& a, const AVector3& b);
    friend  AVector3 operator - (const AVector3& a, const AVector3& b);
    friend  AVector3 operator * (const AVector3& a, double d);
    friend  AVector3 operator * (double d, const AVector3& a);
    friend  AVector3 operator / (const AVector3& a, double d);
    friend  int operator == (const AVector3& a, const AVector3& b);	
    friend  int operator != (const AVector3& a, const AVector3& b);	

    // input output
    friend std::istream& operator>>(std::istream& s, AVector3& v);
    friend std::ostream& operator<<(std::ostream& s, const AVector3& v);

	 // Constants and static functions
    static const AVector3 AxisX;
    static const AVector3 AxisY;
    static const AVector3 AxisZ;
    static const AVector3 Zero;
    static double Dot(const AVector3& a, const AVector3& b); // dot product
    static double Distance(const AVector3& a, const AVector3& b); 
    static double DistanceSqr(const AVector3& a, const AVector3& b); 
    static AVector3 Cross(const AVector3 &left, const AVector3& right);
    static AVector3 Lerp(const AVector3& a, const AVector3& b, float t);

private:

    union 
    {
       struct 
       {
           double mX;
           double mY;
           double mZ;
       };
       double mV[3];
    };
};

#endif

