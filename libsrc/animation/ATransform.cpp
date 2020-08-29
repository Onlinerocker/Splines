#include "ATransform.h"
#include "AMatrix3.h"

const ATransform ATransform::Identity(AQuaternion::Identity, AVector3::Zero);

ATransform::ATransform() : 
    rotation(AQuaternion::Identity),
    translation(AVector3::Zero)
{
}

ATransform::ATransform(const AQuaternion& rot, const AVector3& offset) : 
    rotation(rot), translation(offset)
{
}

ATransform::ATransform(const ATransform& m)
{
    *this = m;
}

// Assignment operators
ATransform& ATransform::operator = (const ATransform& orig)
{
    if (&orig == this)
    {
        return *this;
    }
    rotation = orig.rotation;
    translation = orig.translation;
    return *this;
}

void ATransform::writeToGLMatrix(float* m) const
{
    AMatrix3 mm = rotation.toMatrix();
    m[0] = mm[0][0]; m[4] = mm[0][1]; m[8] = mm[0][2];  m[12] = translation[0];
    m[1] = mm[1][0]; m[5] = mm[1][1]; m[9] = mm[1][2];  m[13] = translation[1];
    m[2] = mm[2][0]; m[6] = mm[2][1]; m[10] = mm[2][2]; m[14] = translation[2];
    m[3] = 0.0f;    m[7] = 0.0f;    m[11] = 0.0f;    m[15] = 1.0f;
}

void ATransform::readFromGLMatrix(float* m)
{
    AMatrix3 mm = rotation.toMatrix();
    mm[0][0] = m[0]; mm[0][1] = m[4]; mm[0][2] = m[8];  translation[0] = m[12];
    mm[1][0] = m[1]; mm[1][1] = m[5]; mm[1][2] = m[9];  translation[1] = m[13];
    mm[2][0] = m[2]; mm[2][1] = m[6]; mm[2][2] = m[10]; translation[2] = m[14];
    rotation = mm.toQuaternion();
}

std::ostream& operator << (std::ostream& s, const ATransform& t)
{
    s << "R: " << t.rotation << " T: " << t.translation << " ";
    return s;
}
