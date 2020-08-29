#include "Cubic.h"
#include "AGLObjects.h"
#include <cmath>

Cubic::Cubic()
{
}

Cubic::~Cubic()
{
}

void Cubic::setB0(const AVector3& b0)
{
    _b0 = b0;
}

void Cubic::setB1(const AVector3& b1)
{
    _b1 = b1;
}

void Cubic::setB2(const AVector3& b2)
{
    _b2 = b2;
}

void Cubic::setB3(const AVector3& b3)
{
    _b3 = b3;
}

const AVector3& Cubic::b0() const
{
    return _b0;
}

const AVector3& Cubic::b1() const
{
    return _b1;
}

const AVector3& Cubic::b2() const
{
    return _b2;
}

const AVector3& Cubic::b3() const
{
    return _b3;
}

void Cubic::setColor(const AVector3& color)
{
    _color = color;
}

const AVector3& Cubic::color() const
{
    return _color;
}

void Cubic::draw()
{
    // your code here
    for(double x=0; x<=1-0.001; x+=0.001){
        AVector3 pt = this->interpolate(x);
        ASetColor(this->_color);
        ADrawLine(pt, this->interpolate(x+0.001));
    }
}

CubicDeCasteljau::CubicDeCasteljau()
{
}

CubicDeCasteljau::~CubicDeCasteljau()
{
}

AVector3 cubicLerp(AVector3 pos, AVector3 pos1, double t){
    return (1.0 - t) * pos + (t*pos1);
}

AVector3 CubicDeCasteljau::interpolate(double t) const
{
    // your code here
    AVector3 b0Prime = cubicLerp(this->_b0, this->_b1, t);
    AVector3 b1Prime = cubicLerp(this->_b1, this->_b2, t);
    AVector3 b2Prime = cubicLerp(this->_b2, this->_b3, t);

    AVector3 b0Prime1 = cubicLerp(b0Prime, b1Prime, t);
    AVector3 b1Prime1 = cubicLerp(b1Prime, b2Prime, t);

    AVector3 ans = cubicLerp(b0Prime1, b1Prime1, t);

    return ans;
}

CubicBernstein::CubicBernstein()
{
}

CubicBernstein::~CubicBernstein()
{
}

AVector3 CubicBernstein::interpolate(double t) const
{
    // your code here
    AVector3 pt0 = pow(1-t, 3) * this->_b0;
    AVector3 pt1 = (3*t) * pow(1-t, 2) * this->_b1;
    AVector3 pt2 = 3 * pow(t, 2) * (1 - t) * this->_b2;
    AVector3 pt3 = pow(t, 3) * this->_b3;

    AVector3 ans = pt0 + pt1 + pt2 + pt3;

    return ans;
}


