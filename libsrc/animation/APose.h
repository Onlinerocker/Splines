#ifndef APose_H_
#define APose_H_

#include "AVector3.h"
#include "AQuaternion.h"
#include <vector>

class APose
{
public:
    APose();
    APose(const AVector3& p);
    APose(const AQuaternion& q);
    APose(const AVector3& pos, const AQuaternion& rot);
    APose(const APose& p);
    APose& operator = (const APose& p);
    virtual ~APose();

    static APose Lerp(const APose& p1, const APose& p2, double u);

    friend std::istream& operator>>(std::istream& s, APose& v);
    friend std::ostream& operator<<(std::ostream& s, const APose& v);

public:
    AVector3 rootPos;
    std::vector<AQuaternion> jointRots;
};

#endif

