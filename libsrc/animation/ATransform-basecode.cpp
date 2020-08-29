#include "ATransform.h"
#include "AMatrix3.h"

ATransform ATransform::inverse() const
{
    AVector3 newVec = -(rotation.inverse()*translation);

    ATransform trans(rotation.inverse(), newVec);
    return trans;
}

AVector3 ATransform::transformPoint(const AVector3& pos) const
{
    AVector3 ans = rotation*pos + translation;
    return ans;
}

AVector3 ATransform::transformVector(const AVector3& dir) const
{
    AVector3 ans = rotation*dir;
    return ans;
}

ATransform operator * (const ATransform& t1, const ATransform& t2)
{
    AQuaternion newRot = t1.rotation * t2.rotation;
    AVector3 vec = t1.rotation * t2.translation + t1.translation;

    return ATransform(newRot, vec);
}

