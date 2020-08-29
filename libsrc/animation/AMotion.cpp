#include "AMotion.h"
#include <cmath>

AMotion::AMotion(double fps) :
    mDt(1.0/fps),
    mFps(fps)
{
}

AMotion::~AMotion() 
{
}

void AMotion::update(ASkeleton& skeleton, double time, bool loop) const
{
    APose pose = getValue(time, loop); 
    skeleton.setPose(pose);
}

void AMotion::setFramerate(double fps)
{
    mFps = fps;
    mDt = 1/fps;
}

double AMotion::getFramerate() const
{
    return mFps;
}

void AMotion::setDeltaTime(double dt)
{
    mDt = dt;
    mFps = 1/dt;
}

double AMotion::getDeltaTime() const
{
    return mDt;
}

void AMotion::editKey(int keyID, const APose& value)
{
    assert(keyID >= 0 && keyID < (int) mKeys.size());
    mKeys[keyID] = value;
}

void AMotion::appendKey(const APose& value)
{
    mKeys.push_back(value);
}

void AMotion::deleteKey(int keyID)
{
    assert(keyID >= 0 && keyID < (int) mKeys.size());
    mKeys.erase(mKeys.begin() + keyID);
}

APose AMotion::getKey(int keyID) const
{
    assert(keyID >= 0 && keyID < (int) mKeys.size());
    return mKeys[keyID];
}

int AMotion::getNumKeys() const
{
    return (int) mKeys.size();
}

void AMotion::clear()
{
    mKeys.clear();
}

double AMotion::getDuration() const 
{
    return (mKeys.size() - 1) * mDt;
}

double AMotion::getNormalizedDuration(double t) const 
{
    return fmod(t, getDuration()) / getDuration(); 
}

int AMotion::getKeyID(double t) const
{
    if (mKeys.size() == 0) return 0;

    t = getNormalizedDuration(t) * getDuration();
    return (int)(t / mDt); 
}

APose AMotion::getValue(double t, bool loop) const
{
    if (mKeys.size() == 0) return APose();

    if (loop)
    {
        t = getNormalizedDuration(t) * getDuration();
    }
    else
    {
        if (t >= getDuration()-A_EPSILON) return mKeys[mKeys.size()-1];
        else if (t < 0) return mKeys[0];
    }

    int segment = (int)(t / mDt); // assumes uniform spacing
    double u = (t - segment*mDt)/mDt;
    return APose::Lerp(mKeys[segment], mKeys[segment+1], u); 
}
