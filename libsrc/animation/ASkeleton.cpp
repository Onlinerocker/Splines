#include "ASkeleton.h"
#include <cstring>

ASkeleton::ASkeleton() : mRoot(0)
{
}

ASkeleton::ASkeleton(const ASkeleton& skeleton)
{
    *this = skeleton;
}

ASkeleton& ASkeleton::operator = (const ASkeleton& orig)
{
    // Performs a deep copy
    if (&orig == this)
    {
        return *this;
    }

    mJoints.clear();
    mRoot = 0;

    // Copy joints
    for (unsigned int i = 0; i < orig.mJoints.size(); i++)
    {
        AJoint* joint = new AJoint(*(orig.mJoints[i]));
        mJoints.push_back(joint);
        //std::cout << "Copy " << joint->GetName() << std::endl;
    }

    // Copy parent/children relationships
    for (unsigned int i = 0; i < orig.mJoints.size(); i++)
    {
        AJoint* joint = orig.mJoints[i];
        if (joint->getParent())
        {
            AJoint* parent = mJoints[joint->getParent()->getID()];
            mJoints[i]->setParent(parent);
        }
        else
        {
            mRoot = mJoints[i];
            mRoot->setParent(0);
        }

        for (int j = 0; j < joint->getNumChildren(); j++)
        {
            AJoint* child = mJoints[joint->getChildAt(j)->getID()];
            mJoints[i]->appendChild(child);
        }
    }

    return *this;
}

ASkeleton::~ASkeleton()
{
    clear();
}

void ASkeleton::clear()
{
    mRoot = NULL;
    mJoints.clear();
}

void ASkeleton::fk()
{
    if (!mRoot) return; // Nothing loaded
    mRoot->fk();
}

void ASkeleton::setPose(const APose& pose)
{
    for (int i = 0; i < getNumJoints(); i++)
    {
        AJoint* joint = getByID(i);
        if (i==0) joint->setLocalTranslation(pose.rootPos);
        joint->setLocalRotation(pose.jointRots[i]);
    }
    fk();
}

AJoint* ASkeleton::getByName(const std::string& name) const
{
    for (unsigned int i = 0; i < mJoints.size(); i++)
    {
        if (name == mJoints[i]->getName())
        {
            return mJoints[i];
        }
    }
    return NULL;
}

AJoint* ASkeleton::getByID(int id) const
{
    assert(id >= 0 && id < (int) mJoints.size());
    return mJoints[id];
}

AJoint* ASkeleton::getRoot() const
{
    return mRoot;
}

void ASkeleton::addJoint(AJoint* joint, AJoint* parent)
{
    joint->setID(mJoints.size());
    mJoints.push_back(joint);
    if (!parent) 
    {
        mRoot = joint;
    }
    else
    {
        AJoint::Attach(parent, joint);
    }
}

void ASkeleton::deleteJoint(const std::string& name)
{
    AJoint* joint = getByName(name);
    if (!joint) return; // no work to do

    for (int i = 0; i < joint->getNumChildren(); i++)
    {
        AJoint* child = joint->getChildAt(i);
        AJoint::Detach(joint, child);
        deleteJoint(child->getName());
    }

    // Re-assign ids and delete orphans
    AJoint* parent = joint->getParent();
    if (parent)
    {
        AJoint::Detach(parent, joint);
        if (parent->getNumChildren() == 0) parent->setNumChannels(0);
    }
    for (int i = joint->getID(); i < (int) mJoints.size() - 1; i++)
    {
        mJoints[i] = mJoints[i + 1];
        mJoints[i]->setID(i);
    }
    mJoints.resize(mJoints.size() - 1);
    delete joint;
}
