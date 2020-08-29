#ifndef IKController_H_
#define IKController_H_

#include "ASkeleton.h"

class AIKController
{
public:
    AIKController(double eps = 1.0) : _epsilon(eps), _selectedJoint(-1) {}
    virtual ~AIKController() {}

    bool solveIKTwoLink(ASkeleton& skeleton, 
        const AVector3& goalPos);

    bool solveIKAnalytic(ASkeleton& skeleton, 
        int jointid, const AVector3& goalPos);

    bool solveIKCCD(ASkeleton& skeleton, 
        int jointid, const AVector3& goalPos, 
        int chainSize = -1, int maxIters = 50, 
        float nudgeFactor = 0.1); 

    void setEpsilon(double eps);
    double getEpsilon() const;

protected:
    void computeJointChain(ASkeleton& skeleton, 
        int selectedJoint, int chainSize);

    double _epsilon;
    int _selectedJoint;
    std::vector<AJoint*> _chain;
};

#endif
