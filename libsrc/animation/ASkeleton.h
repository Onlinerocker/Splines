#ifndef ASkeleton_H_
#define ASkeleton_H_

#include "AJoint.h"
#include "APose.h"
#include <vector>

class ASkeleton
{
public:
    // constructors
    ASkeleton();
    ASkeleton(const ASkeleton& skeleton); // Deep copy
    virtual ASkeleton& operator=(const ASkeleton& orig); // Deep copy

    // destructor
    virtual ~ASkeleton();

    // forward kinematics
    // calling this method updates the local2global transforms for each joint
    virtual void fk();

    // removes all joints from the skeleton
    virtual void clear();

    // returns the joint having the given name
    // returns null if no joint has the given name
    AJoint* getByName(const std::string& name) const;

    // returns the joint corresponding to id
    // joint ids start at zero and are numbered in the order they are 
    //    added to the skeleton. The root joint has id = 0
    // ids must be in the range [0, numJoints-1]
    AJoint* getByID(int id) const;

    // returns the root joint
    AJoint* getRoot() const;

    // adds a joint to this skeleton
    // if the parent is NULL, this joint is assumed to be the root
    void addJoint(AJoint* joint, AJoint* parent = NULL);

    // deletes a joint from the skeleton
    // recursively deletes all children of this joint
    // does nothing if no joint corresponding to name is found
    // warning: this function will reassign joint ids
    void deleteJoint(const std::string& name);

    // returns the number of joints
    int getNumJoints() const { return (int) mJoints.size(); }

    // sets the joints of this skeleton to match pose
    // APose stores the local rotations of each joint
    // Assumes that the joints in pose (quantity and order)
    //     matches this skeleton
    void setPose(const APose& pose);

protected:
    std::vector<AJoint*> mJoints;
    AJoint* mRoot;
};

#endif
