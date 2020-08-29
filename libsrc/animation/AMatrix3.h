#ifndef aMatrix3_H_
#define aMatrix3_H_

#include <iostream>
#include "AVector3.h"

class AQuaternion;
class AMatrix3
{
public:

    // Constructors
    AMatrix3();
    AMatrix3(double a11, double a12, double a13,
             double a21, double a22, double a23,
             double a31, double a32, double a33);
    AMatrix3(const AMatrix3& m);
    AMatrix3(const AVector3& axis, double angleRad);
    AMatrix3(const AQuaternion& q);

    enum RotOrder { XYZ, XZY, YXZ, YZX, ZXY, ZYX };
    AMatrix3(RotOrder roo, const AVector3& eulerRad);

    // Static functions
    static AMatrix3 Identity;
    static AMatrix3 Zero;

	 // Conversion with euler angles
    AVector3 toEulerAngles(RotOrder roo) const;
    AVector3 toEulerAnglesXYZ() const;
    AVector3 toEulerAnglesXZY() const;
    AVector3 toEulerAnglesYXZ() const;
    AVector3 toEulerAnglesYZX() const;
    AVector3 toEulerAnglesZXY() const;
    AVector3 toEulerAnglesZYX() const;
    void fromEulerAngles(RotOrder roo, const AVector3& anglesRad);
    void fromEulerAnglesXYZ(const AVector3& anglesRad);
    void fromEulerAnglesXZY(const AVector3& anglesRad);
    void fromEulerAnglesYXZ(const AVector3& anglesRad);
    void fromEulerAnglesYZX(const AVector3& anglesRad);
    void fromEulerAnglesZXY(const AVector3& anglesRad);
    void fromEulerAnglesZYX(const AVector3& anglesRad);

	 void fromAxisAngle(const AVector3& axis, double rad);
	 void toAxisAngle(AVector3& axis, double& rad) const;

    // Conversion with Quaternion
    AQuaternion toQuaternion() const;
    void fromQuaternion(const AQuaternion& q);

    // Assignment operators
    AMatrix3& operator = ( const AMatrix3& m );	    // assignment of a mat3
    AMatrix3& operator += ( const AMatrix3& m );	    // incrementation by a mat3
    AMatrix3& operator -= ( const AMatrix3& m );	    // decrementation by a mat3
    AMatrix3& operator *= ( double d );	    // multiplication by a constant
    AMatrix3& operator /= ( double d );	    // division by a constant
    double* operator [] (int i);					// indexing
    const double* operator [] ( int i) const;		// read-only indexing

    // special functions
    AMatrix3 transpose() const;
    void writeToGLMatrix(float* m) const;
    void readFromGLMatrix(float* m);

    // friends
    friend AMatrix3 operator - (const AMatrix3& a);						// -m1
    friend AMatrix3 operator + (const AMatrix3& a, const AMatrix3& b);	    // m1 + m2
    friend AMatrix3 operator - (const AMatrix3& a, const AMatrix3& b);	    // m1 - m2
    friend AMatrix3 operator * (const AMatrix3& a, const AMatrix3& b);		// m1 * m2
    friend AMatrix3 operator * (const AMatrix3& a, double d);	    // m1 * 3.0
    friend AMatrix3 operator * (double d, const AMatrix3& a);	    // 3.0 * m1
    friend AMatrix3 operator / (const AMatrix3& a, double d);	    // m1 / 3.0
    friend int operator == (const AMatrix3& a, const AMatrix3& b);	    // m1 == m2 ?
    friend int operator != (const AMatrix3& a, const AMatrix3& b);	    // m1 != m2 ?

    friend std::istream& operator >> (std::istream& s, AMatrix3& v);
    friend std::ostream& operator << (std::ostream& s, const AMatrix3& v);

    friend AVector3 operator * (const AMatrix3& a, const AVector3& v);	    // linear transform
    friend AMatrix3 operator * (const AMatrix3& a, const AMatrix3& b);	// matrix 3 product

private:
	 union
	 {
	 	 struct
	    {
		     double m11;
		     double m12;
		     double m13;
		     double m21;
		     double m22;
		     double m23;
		     double m31;
		     double m32;
		     double m33;
	    };
		 double mM[3][3];
	 };
};

#endif

