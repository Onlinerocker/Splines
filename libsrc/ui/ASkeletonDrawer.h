#ifndef ACHARACTERDRAWER_H_
#define ACHARACTERDRAWER_H_

#include "ASkeleton.h"

class ASkeletonDrawer 
{
public:
	ASkeletonDrawer();
	virtual ~ASkeletonDrawer();

    void setColor(const AVector3& c);
    AVector3 getColor() const;

    void setJointRadius(float r);
    float getJointRadius() const;

    void setAxisLength(float r);
    float getAxisLength() const;

    void setShowAxis(bool b);
    bool getShowAxis() const;

    void setOffsetPosition(const AVector3& p);
    AVector3 getOffsetPosition() const;

    void setOffsetRotation(const AMatrix3& m);
    AMatrix3 getOffsetRotation() const;

    void setScale(float m);
    float getScale() const;

	virtual void draw(const ASkeleton& skeleton);

protected:

    virtual void drawJoint(const ATransform& globalTransform);
    virtual void drawBodyParts(AJoint* currentJoint);

protected:
    AVector3 _color;
    AVector3 _offsetPosition;
    AMatrix3 _offsetRotation;
    float _scale;
    float _axisLength;
    float _jointRadius;
    bool _drawAxes;

};

#endif
