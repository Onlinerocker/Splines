#include "AIKController.h"
#include <cmath>

bool AIKController::solveIKTwoLink(ASkeleton& skeleton, 
    const AVector3& goalPos)
{
    // Assume that skeleton is a two link chain 
    // solve for rotations for the first and second joint 
    // such that the position of the last joint is at goalPos
    AJoint* root = skeleton.getRoot();
    AJoint* j1 = root->getChildAt(0);
    AJoint* j2 = j1->getChildAt(0);

    double l1 = j1->getLocal2Parent().translation.length();
    double l2 = j2->getLocal2Parent().translation.length();

    double r = (goalPos - root->getLocal2Global().translation).length();
    
    double rad = ((r * r) - (l1 * l1) - (l2 * l2)) / (-2 * l1 * l2);
    rad = acos(rad);

    double theta2Z = rad - M_PI;
    if(r > (l1 + l2))
        theta2Z = 0;
    if(r < (std::abs(l1 - l2)))
        theta2Z = -M_PI;

    j1->setLocalRotation(AQuaternion(AVector3(0,0,1), theta2Z));
    skeleton.fk();

    double theta1Z = (-l2 * sin(theta2Z)) / r;
    theta1Z = asin(theta1Z);

    double beta = atan2(goalPos.z(), goalPos.x());
    double gamma = asin(goalPos.y() / r);

    AMatrix3 mat;
    mat.fromEulerAnglesYZX(AVector3(0, -beta, gamma));
    AQuaternion finalRootRot = AQuaternion(mat) * AQuaternion(AVector3(0,0,1), theta1Z);
    root->setLocalRotation(finalRootRot);

    skeleton.fk();

    return true;
}

bool AIKController::solveIKAnalytic(ASkeleton& skeleton, 
    int jointid, const AVector3& goalPos)
{
	if (jointid == -1) return true;
    if (jointid < 0 || jointid > skeleton.getNumJoints()) return false;

    AJoint* joint = skeleton.getByID(jointid);
    if (!joint->getParent()) //parent check
    {
        std::cout << "Warning: solveIKAnalytic() needs joint "
            "with parent and grandparent\n";
        return false;
    }

    AJoint* parent = joint->getParent();
    if (!parent->getParent()) //grand parent check
    {
        std::cout << "Warning: solveIKAnalytic() needs joint "
            "with parent and grandparent\n";
        return false;
    }

    AJoint* grandParent = parent->getParent();
    AVector3 parDir = parent->getLocalTranslation();
    
    parDir.normalize();
    AVector3 parAx = AVector3::Cross(parDir, AVector3(0,0,-1));
    if(parDir[1] < 0)
        parAx = AVector3::Cross(parDir, AVector3(0,0,1));

    double l1 = parent->getLocal2Parent().translation.length();
    double l2 = joint->getLocal2Parent().translation.length();

    double r = (goalPos - grandParent->getLocal2Global().translation).length();

    double rad = ((r * r) - (l1 * l1) - (l2 * l2)) / (-2 * l1 * l2);
    rad = acos(rad);

    double theta2Z = rad - M_PI;
    if(r > (l1 + l2))
    {
        theta2Z = 0;
    }
        
    if(r < (std::abs(l1 - l2)))
    {
        theta2Z = -M_PI;
    }
        
    AQuaternion rot = AQuaternion(parAx, theta2Z);
    parent->setLocalRotation(rot);
    parent->fk();

    AVector3 err = goalPos - joint->getGlobalTranslation();
    AVector3 dir = joint->getGlobalTranslation() - grandParent->getGlobalTranslation();
    AVector3 cross = AVector3::Cross(dir, err);

    AVector3 axis;
    double phi;
    AQuaternion locQuat;

    if(fabs(cross.length()) <= A_EPSILON){
        locQuat = grandParent->getLocalRotation();
    }else{
        axis = cross / cross.length();
        if(grandParent->getParent() != NULL)
            axis = grandParent->getParent()->getLocal2Global().inverse().transformVector(axis);
        phi = atan2(cross.length(), AVector3::Dot(dir,dir) + AVector3::Dot(dir,err));    
        //locQuat = AQuaternion(axis,phi) * grandParent->getGlobalRotation();
        grandParent->setLocalRotation(AQuaternion(axis, phi) * grandParent->getLocalRotation());
        grandParent->fk();
    }    
    return true;
}

bool AIKController::solveIKCCD(ASkeleton& skeleton, int jointid, 
    const AVector3& goalPos, int chainSize, int maxIters, float nudgeFactor)
{
    if (_selectedJoint != jointid || chainSize != (int) _chain.size())
    {
        computeJointChain(skeleton, jointid, chainSize);
    }

    // There are no joints in the IK chain for manipulation
    if (_chain.size() == 0) return true;

    AJoint* end = skeleton.getByID(jointid);
    for(int x=0; x < maxIters; x++)
    {
        //if(end->getGlobalTranslation() - goalPos <= epsilon)
        AJoint* cur = end->getParent();
        AVector3 dir;
        AVector3 err;
        for(int j=0; j < _chain.size(); j++)
        {
            err = goalPos - end->getGlobalTranslation();
            if(err.length() <= A_EPSILON)
                return true;

            dir = end->getGlobalTranslation() - cur->getGlobalTranslation();
            AVector3 cross = AVector3::Cross(dir, err);
            AVector3 axis;
            double phi;
            AQuaternion locQuat;

            if(fabs(cross.length()) <= A_EPSILON){
                locQuat = cur->getLocalRotation();
            }else{
                axis = cross / cross.length();
                axis = cur->getParent()->getLocal2Global().inverse().transformVector(axis);
                phi = atan2(cross.length(), AVector3::Dot(dir,dir) + AVector3::Dot(dir,err));    
                //locQuat = AQuaternion(axis,nudgeFactor*phi) * cur->getGlobalRotation();
                cur->setLocalRotation(AQuaternion(axis, nudgeFactor * phi) * cur->getLocalRotation());
            }      

            cur->fk();
            cur = cur->getParent();
        }
    }

    return false;
}

