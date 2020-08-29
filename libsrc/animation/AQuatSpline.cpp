#include <cmath>
#include "AQuatSpline.h"
#include "AQuaternion.h"

AQuatSpline::AQuatSpline()  
{
}

AQuatSpline::~AQuatSpline()
{
}

void AQuatSpline::editKey(int keyID, const AQuaternion& value)
{
    assert(keyID >= 0 && keyID < (int) mKeys.size());
    mKeys[keyID] = value;
}

int AQuatSpline::appendKey(double time, const AQuaternion& value)
{
    mKeys.push_back(value);
    mTimes.push_back(time);
    return mKeys.size();
}

void AQuatSpline::deleteKey(int keyID)
{
    assert(keyID >= 0 && keyID < (int) mKeys.size());
    mKeys.erase(mKeys.begin() + keyID);
    mTimes.erase(mTimes.begin() + keyID);
}

AQuaternion AQuatSpline::getKey(int keyID) const
{
    assert(keyID >= 0 && keyID < (int) mKeys.size());
    return mKeys[keyID];
}

double AQuatSpline::getTime(int keyID) const
{
    assert(keyID >= 0 && keyID < (int) mKeys.size());
    return mTimes[keyID];
}

int AQuatSpline::getNumKeys() const
{
    return (int) mKeys.size();
}

void AQuatSpline::clear()
{
    mKeys.clear();
    mTimes.clear();
}

double AQuatSpline::getDuration() const 
{
    if (mKeys.size() == 0) return 0;
    int lastIdx = mKeys.size() - 1;
    return mTimes[lastIdx];
}

double AQuatSpline::getNormalizedDuration(double t) const 
{
    double frac = fmod(t, getDuration());
    return frac / getDuration();
}

int AQuatSpline::getKeyID(double t) const
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

int AQuatSpline::getNumSegments() const
{
   if (mKeys.size() > 1) return mKeys.size()-1;
   return 0;
}

int AQuatSpline::computeSegment(double t) const
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

AQuaternion AQuatSpline::getValue(double t, bool loop) const
{
    if (mKeys.size() == 0) return AQuaternion();
    if (mKeys.size() == 1) return mKeys[0];

    if (loop)
    {
        t = getNormalizedDuration(t) * getDuration();
    }
    else
    {
        if (t >= getDuration()-A_EPSILON) return mKeys[mKeys.size()-1];
        else if (t < mTimes[0]) return mKeys[0];
    }

    int segment = computeSegment(t);
    double u = (t - mTimes[segment])/(mTimes[segment+1] - mTimes[segment]);
    AQuaternion q0 = mKeys[segment];
    AQuaternion q1 = mKeys[segment+1];
    return AQuaternion::Slerp(q0, q1, u); 
}

