#include "AJoint.h"
#include <cstring>

AJoint::AJoint() : 
    mId(-1), 
    mName(""), 
    mChannelCount(6), 
    mRotOrder("xyz"), 
    mDirty(false),
    mParent(0),
    mChildren(),
    mLocal2Parent(),
    mLocal2Global()
{

}

AJoint::AJoint(const std::string& name) :
    mId(-1),
    mName(name),
    mChannelCount(6),
    mRotOrder("xyz"),
    mDirty(false),
    mParent(0),
    mChildren(),
    mLocal2Parent(),
    mLocal2Global()
{

}

AJoint::AJoint(const AJoint& joint)
{
    *this = joint;
}

AJoint& AJoint::operator=(const AJoint& orig)
{
    if (&orig == this)
    {
        return *this;
    }

    // copy everything except parents/children
    mParent = 0;
    mChildren.clear();
    mDirty = true;

    mId = orig.mId;
    mName = orig.mName;
    mChannelCount = orig.mChannelCount;
    mRotOrder = orig.mRotOrder;
    mLocal2Parent = orig.mLocal2Parent;
    mLocal2Global = orig.mLocal2Global;

    return *this;
}

AJoint::~AJoint()
{

}

AJoint* AJoint::getParent()
{
    return mParent;
}
void AJoint::setParent(AJoint* parent)
{
    mParent = parent;
}

int AJoint::getNumChildren() const
{
    return mChildren.size();
}
AJoint* AJoint::getChildAt(int index)
{
    assert(index >= 0 && index < (int) mChildren.size());
    return mChildren[index];
}
void AJoint::appendChild(AJoint* child)
{
    mChildren.push_back(child);
}

void AJoint::setName(const std::string& name)
{
    mName = name;
}
void AJoint::setID(int id)
{
    mId = id;
    if (strncmp("Site", mName.c_str(), 4) == 0)
    {
        char dummy[32];
        sprintf(dummy, "Site%d", mId);
        mName = dummy;
    }
}
void AJoint::setNumChannels(int count)
{
    mChannelCount = count;
}
void AJoint::setRotationOrder(const std::string& _order)
{
    std::string order = _order;

    if (order.find("Zrotation Xrotation Yrotation") != std::string::npos) mRotOrder = "zxy";
    else if (order.find("Zrotation Yrotation Xrotation") != std::string::npos) mRotOrder = "zyx";
    else if (order.find("Xrotation Yrotation Zrotation") != std::string::npos) mRotOrder = "xyz";
    else if (order.find("Xrotation Zrotation Yrotation") != std::string::npos) mRotOrder = "xzy";
    else if (order.find("Yrotation Xrotation Zrotation") != std::string::npos) mRotOrder = "yxz";
    else if (order.find("Yrotation Zrotation Xrotation") != std::string::npos) mRotOrder = "yzx";
    else mRotOrder = order;

}

void AJoint::setLocal2Parent(const ATransform& transform)
{
    mLocal2Parent = transform;
}
void AJoint::setLocalTranslation(const AVector3& translation)
{
    mLocal2Parent.translation = translation;
}
void AJoint::setLocalRotation(const AQuaternion& rotation)
{
    mLocal2Parent.rotation = rotation;
}

int AJoint::getID() const
{
    return mId;
}
const std::string& AJoint::getName() const
{
    return mName;
}
int AJoint::getNumChannels() const
{
    return mChannelCount;
}
const std::string& AJoint::getRotationOrder() const
{
    return mRotOrder;
}

const ATransform& AJoint::getLocal2Parent() const
{
    return mLocal2Parent;
}
const AVector3& AJoint::getLocalTranslation() const
{
    return mLocal2Parent.translation;
}
const AQuaternion& AJoint::getLocalRotation() const
{
    return mLocal2Parent.rotation;
}

const ATransform& AJoint::getLocal2Global() const
{
    return mLocal2Global;
}
const AVector3& AJoint::getGlobalTranslation() const
{
    return mLocal2Global.translation;
}
const AQuaternion& AJoint::getGlobalRotation() const
{
    return mLocal2Global.rotation;
}

void AJoint::Attach(AJoint* pParent, AJoint* pChild)
{
    if (pChild)
    {
        AJoint* pOldParent = pChild->mParent;
        if (pOldParent)
        {
            // erase the child from old parent's children list
            std::vector<AJoint*>::iterator iter;
            for (iter = pOldParent->mChildren.begin(); iter != pOldParent->mChildren.end(); iter++)
            {
                if ((*iter) == pChild)
                {
                    iter = pOldParent->mChildren.erase(iter);
                }
            }
        }
        // Set the new parent
        pChild->mParent = pParent;
        // Add child to new parent's children list
        if (pParent)
        {
            pParent->mChildren.push_back(pChild);
        }
    }
}

void AJoint::Detach(AJoint* pParent, AJoint* pChild)
{
    if (pChild && pChild->mParent == pParent)
    {
        if (pParent)
        {
            // erase the child from parent's children list
            for (int i = 0; i < (int) pParent->mChildren.size(); i++)
            {
                if (pParent->mChildren[i] == pChild)
                {
                    for (int j = i; j < (int) pParent->mChildren.size() - 1; j++)
                    {
                        pParent->mChildren[j] = pParent->mChildren[j + 1];
                    }
                    pParent->mChildren.resize(pParent->mChildren.size() - 1);
                    break;
                }
            }
        }
        pChild->mParent = NULL;
    }
}

