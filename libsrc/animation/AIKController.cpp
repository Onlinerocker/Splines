#include "AIKController.h"
#include <cmath>

void AIKController::computeJointChain(ASkeleton& skeleton,
    int selectedJoint, int chainSize)
{
    _chain.clear();
    _selectedJoint = selectedJoint;
    if (selectedJoint >= 0 && selectedJoint < (int)skeleton.getNumJoints())
    {
        AJoint* tmp = skeleton.getByID(selectedJoint);
        if (tmp != NULL && tmp->getParent() != NULL)
        {
            // terminate at the joint before root joint, 
            // so that root will not change during IK	
            tmp = tmp->getParent();
            while (tmp->getParent() != NULL)
            {
                _chain.push_back(tmp);
                if (chainSize > -1 && (int) _chain.size() > chainSize) break;
                tmp = tmp->getParent();
            }
        }
    }
}

double AIKController::getEpsilon() const
{
    return _epsilon;
}

void AIKController::setEpsilon(double v)
{
    _epsilon = v;
}

