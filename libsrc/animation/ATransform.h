#ifndef ATransform_H_
#define ATransform_H_

#include "AQuaternion.h"
#include "AVector3.h"

class ATransform
{
public:
    ATransform();
    ATransform(const AQuaternion& rotation, const AVector3& translation);
    ATransform(const ATransform& transform);
    ATransform& operator = (const ATransform& source); 

    ATransform inverse() const;
    AVector3 transformPoint(const AVector3& pos) const;
    AVector3 transformVector(const AVector3& dir) const;

    friend ATransform operator * (const ATransform& a, const ATransform& b); // m1 * m2
    friend std::ostream& operator << (std::ostream& s, const ATransform& v); // for printing to cout
    void writeToGLMatrix(float* m) const;	
    void readFromGLMatrix(float* m);

public:
    AQuaternion rotation;
    AVector3 translation;

public:
    static const ATransform Identity;
};
#endif

