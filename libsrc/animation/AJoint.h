#ifndef AJoint_H_
#define AJoint_H_

#include "ATransform.h"
#include <vector>

// Classes for organizing animatble transforms into hierachies

class AJoint
{
public:
    AJoint();
    AJoint(const std::string& name);
    AJoint(const AJoint& joint);
    virtual AJoint& operator=(const AJoint& joint);

    virtual ~AJoint();

    AJoint* getParent();
    void setParent(AJoint* parent);

    int getNumChildren() const;
    AJoint* getChildAt(int index);
    void appendChild(AJoint* child);

    void fk();

    void setName(const std::string& name);
    void setID(int id);
    void setNumChannels(int count);
    void setRotationOrder(const std::string& order);

    void setLocal2Parent(const ATransform& transform);
    void setLocalTranslation(const AVector3& translation);
    void setLocalRotation(const AQuaternion& rotation);

    int getID() const;
    const std::string& getName() const;
    int getNumChannels() const;
    const std::string& getRotationOrder() const;

    const ATransform& getLocal2Parent() const;
    const AVector3& getLocalTranslation() const;
    const AQuaternion& getLocalRotation() const;

    const ATransform& getLocal2Global() const;
    const AVector3& getGlobalTranslation() const;
    const AQuaternion& getGlobalRotation() const;

    static void Attach(AJoint* pParent, AJoint* pChild);
    static void Detach(AJoint* pParent, AJoint* pChild);

protected:

    int mId;
    std::string mName;
    int mChannelCount;
    std::string mRotOrder;
    bool mDirty;

    AJoint* mParent;
    std::vector<AJoint*> mChildren;

    ATransform mLocal2Parent;
    ATransform mLocal2Global;
};

typedef AJoint AnimatableTransform;

#endif
