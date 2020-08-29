#ifndef aQuaternion_H_
#define aQuaternion_H_

#include <iostream>
#include "AQuaternion.h"
#include "AMatrix3.h"
#include "AVector3.h"

class AQuaternion
{
public:

    // Constructors
    AQuaternion();
    AQuaternion(double x, double y, double z, double w);
    AQuaternion(const AMatrix3& m);
    AQuaternion(const AVector3& axis, double rad);
    AQuaternion(const AQuaternion& q);

    // Static functions
    static double Dot(const AQuaternion& q0, const AQuaternion& q1);
    static AQuaternion Slerp(const AQuaternion& q0, 
        const AQuaternion& q1, double t);

    // Conversion functions
    void toAxisAngle (AVector3& axis, double& angleRad) const;
    void fromAxisAngle (const AVector3& axis, double angleRad);

    AMatrix3 toMatrix () const;
    void fromMatrix (const AMatrix3& rot);

    // Assignment operators
    AQuaternion& operator = (const AQuaternion& q);	
    AQuaternion& operator += (const AQuaternion& q);
    AQuaternion& operator -= (const AQuaternion& q);
    AQuaternion& operator *= (const AQuaternion& q);
    AQuaternion& operator *= (double d);
    AQuaternion& operator /= (double d);

    // Indexing
    double w() const;
    double x() const;
    double y() const;
    double z() const;
    double& operator[](int i); 
    double operator[](int i) const;

    // Friends
    friend AQuaternion operator- (const AQuaternion& q);					
    friend AQuaternion operator+ (const AQuaternion& q0, const AQuaternion& q1);
    friend AQuaternion operator- (const AQuaternion& q0, const AQuaternion& q1);
    friend AQuaternion operator* (const AQuaternion& q, double d);
    friend AVector3 operator* (const AQuaternion& q, const AVector3& v);
    friend AQuaternion operator* (double d, const AQuaternion& q);	
    friend AQuaternion operator* (const AQuaternion& q0, const AQuaternion& q1);
    friend AQuaternion operator/ (const AQuaternion& q, double d);
    friend bool operator== (const AQuaternion& q0, const AQuaternion& q1);
    friend bool operator!= (const AQuaternion& q0, const AQuaternion& q1);

    friend std::istream& operator>> (std::istream& s, AQuaternion& v);
    friend std::ostream& operator<< (std::ostream& s, const AQuaternion& v);

    // Special functions
    double length() const;
    double sqrLength() const;
    void normalize();
    AQuaternion normalized() const;
    AQuaternion inverse() const;

	// static constants
	static AQuaternion Zero;
	static AQuaternion Identity;

private:

    union
	 {
	 	 struct
	 	 {
			 double mX;
			 double mY;
			 double mZ;
			 double mW;
		 };
	 	 double mV[4];
	 };
};


#endif

