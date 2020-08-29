#include <cmath>
#include "ASpline.h"
#include "AVector3.h"

ASpline::ASpline() : 
    mDirty(true),
    mInterpolator(new AInterpolatorLinear())
{
}

ASpline::~ASpline()
{
    delete mInterpolator;
}

void ASpline::setInterpolationType(const std::string& name)
{
    delete mInterpolator;
    if (name == "Catmull-Rom") mInterpolator = new AInterpolatorCatmullRom();
    if (name == "Linear") mInterpolator = new AInterpolatorLinear();
    if (name == "Hermite") mInterpolator = new AInterpolatorHermite();
    mDirty = true;
}

const std::string& ASpline::getInterpolationType() const
{
    return mInterpolator->getType();
}

void ASpline::editKey(int keyID, const AVector3& value)
{
    assert(keyID >= 0 && keyID < (int) mKeys.size());
    mKeys[keyID] = value;
    mDirty = true;
}

int ASpline::appendKey(double time, const AVector3& value)
{
    mKeys.push_back(value);
    mTimes.push_back(time);
    mDirty = true;
    return mKeys.size();
}

void ASpline::deleteKey(int keyID)
{
    assert(keyID >= 0 && keyID < (int) mKeys.size());
    mKeys.erase(mKeys.begin() + keyID);
    mTimes.erase(mTimes.begin() + keyID);
    mDirty = true;
}

AVector3 ASpline::getKey(int keyID) const
{
    assert(keyID >= 0 && keyID < (int) mKeys.size());
    return mKeys[keyID];
}

double ASpline::getTime(int keyID) const
{
    assert(keyID >= 0 && keyID < (int) mKeys.size());
    return mTimes[keyID];
}

int ASpline::getNumKeys() const
{
    return (int) mKeys.size();
}

void ASpline::clear()
{
    mKeys.clear();
    mTimes.clear();
    mInterpolator->clearControlPoints();
}

double ASpline::getDuration() const 
{
    if (mKeys.size() == 0) return 0;
    int lastIdx = mKeys.size() - 1;
    return mTimes[lastIdx];
}

double ASpline::getNormalizedDuration(double t) const 
{
    double frac = fmod(t, getDuration());
    return frac / getDuration();
}

int ASpline::getKeyID(double t) const
{
    if (mTimes.size() == 0) return -1;

    for (unsigned int i = 0; i < mTimes.size(); i++)
    {
       if ((mTimes[i] - t) < A_EPSILON)
       {
           return i;
       }
    }
    return -1;
}

int ASpline::getNumControlPoints() const
{
   return mInterpolator->getNumControlPoints();
}

const AVector3& ASpline::getControlPoint(int id) const
{
   return mInterpolator->getControlPoint(id);
}

int ASpline::getNumSegments() const
{
   if (mKeys.size() > 1) return mKeys.size()-1;
   return 0;
}

const AVector3& ASpline::getControlPoint(int segment, int id) const
{
   return mInterpolator->getControlPoint(segment, id);
}

void ASpline::editControlPoint(int id, const AVector3& v)
{
   mInterpolator->editControlPoint(id, v);
}

int ASpline::computeSegment(double t) const
{
   for (unsigned int i = 0; i < mTimes.size()-1; i++)
   {
      if (mTimes[i] <= t && t < mTimes[i+1])
      {
         return i;
      }
   }
   return -1;
}

AVector3 ASpline::getValue(double t, bool loop) const
{
    if (mKeys.size() == 0) return AVector3();
    if (mKeys.size() == 1) return mKeys[0];


    if (loop)
    {
        t = getNormalizedDuration(t) * getDuration();
    }
    else
    {
        if (t >= getDuration()-A_EPSILON) return mKeys[mKeys.size()-1];
        else if (t < 0) return mKeys[0];
    }

    if (mDirty) 
    {
        mInterpolator->resetControlPoints(mKeys);
        mDirty = false;
    }

    int segment = computeSegment(t);
    double u = (t - mTimes[segment])/(mTimes[segment+1] - mTimes[segment]);
    return mInterpolator->interpolate(segment, u);
}

