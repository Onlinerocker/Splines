#include "APose.h"

APose::APose() {}
APose::~APose() {}

APose::APose(const AVector3& p) : rootPos(p)
{
}

APose::APose(const AQuaternion& q)
{
   jointRots.push_back(q);
}

APose::APose(const AVector3& pos, const AQuaternion& rot) : rootPos(pos)
{
   jointRots.push_back(rot);
}

APose::APose(const APose& p)
{
    assert(jointRots.size() == 0);
    rootPos = p.rootPos;
    for (unsigned int i = 0; i < p.jointRots.size(); i++)
    {
        jointRots.push_back(p.jointRots[i]);
    }
}

APose& APose::operator = (const APose& p)
{
    if (this == &p)
    {
        return *this;
    }

    jointRots.clear();
    rootPos = p.rootPos;
    for (unsigned int i = 0; i < p.jointRots.size(); i++)
    {
        jointRots.push_back(p.jointRots[i]);
    }
    return *this;
}

std::istream& operator>>(std::istream& s, APose& v)
{
    s >> v.rootPos; 

    v.jointRots.clear();
    for (unsigned int i = 0; i < v.jointRots.size(); i++)
    {
        AQuaternion q;
        s >> q;
        v.jointRots.push_back(q);
    }
    return s;
}

std::ostream& operator<<(std::ostream& s, const APose& v)
{
    s << "**************" << std::endl;
    s << v.rootPos << std::endl; 
    for (unsigned int i = 0; i < v.jointRots.size(); i++)
    {
        s << v.jointRots[i] << std::endl;
    }
    return s;
}

APose APose::Lerp(const APose& key1, const APose& key2, double u)
{
    APose pose;
    pose.rootPos = key1.rootPos * (1-u) + key2.rootPos * u;
    for (int i = 0; i < (int) key1.jointRots.size(); i++)
    {
        AQuaternion q1 = key1.jointRots[i];
        AQuaternion q2 = key2.jointRots[i];
        AQuaternion q = AQuaternion::Slerp(q1, q2, u);
        pose.jointRots.push_back(q);
    }
    return pose;
}
