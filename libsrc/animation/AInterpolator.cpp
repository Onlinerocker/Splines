#include "AInterpolator.h"

AInterpolator::AInterpolator(const std::string& type, int num) : 
   mNumControlPointsPerSegment(num),
   mCtrlPoints(),
   mType(type)
{
}

void AInterpolator::editControlPoint(int ID, const AVector3& value)
{
    assert(ID >= 0 && ID < (int) mCtrlPoints.size());
    mCtrlPoints[ID] = value;
}

const AVector3& AInterpolator::getControlPoint(int ID) const
{
    assert(ID >= 0 && ID < (int) mCtrlPoints.size());
    return mCtrlPoints[ID];
}

const AVector3& AInterpolator::getControlPoint(int segment, int ID) const
{
    int idx = computeIndex(segment, ID);
    return mCtrlPoints[idx];
}

int AInterpolator::computeIndex(int segment, int ctrlPtId) const
{
    assert(ctrlPtId >= 0 && ctrlPtId < (int) mNumControlPointsPerSegment);
    return (mNumControlPointsPerSegment-1)*segment + ctrlPtId;
}

void AInterpolator::setControlPoint(int segment, int ID, const AVector3& val) 
{
    assert(ID >= 0 && ID < (int) mNumControlPointsPerSegment);
    unsigned int idx = computeIndex(segment, ID);
    if (idx >= mCtrlPoints.size())
    {
      for (unsigned int i = mCtrlPoints.size(); i <= idx; i++)
      {
         mCtrlPoints.push_back(AVector3::Zero);
      }
    }
    mCtrlPoints[idx] = val;
}

void AInterpolator::clearControlPoints()
{
    mCtrlPoints.clear();
}

int AInterpolator::getNumControlPoints() const
{
    return mCtrlPoints.size();
}

void AInterpolator::resetControlPoints(const std::vector<AVector3>& keys)
{
    int totalPoints = keys.size();
    if (totalPoints <= 1) return;

    computeControlPoints(keys);
}

const std::string& AInterpolator::getType() const 
{ 
   return mType; 
}

int AInterpolator::getNumControlPointsPerSegment() const
{
   return mNumControlPointsPerSegment;
}

int AInterpolatorHermite::computeIndex(int segment, int ctrlPtId) const
{
   return segment*2 + ctrlPtId;
}
