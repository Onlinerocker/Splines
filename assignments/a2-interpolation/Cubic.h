#pragma once

#include "AVector3.h"

class Cubic
{
public:
    Cubic();
    virtual ~Cubic();

    // abstract method for interpolation
    // child classes implement this method using different algorithms
    virtual AVector3 interpolate(double t) const = 0;

    // draws this curve
    virtual void draw();

    // setters for control points and color
    void setB0(const AVector3& b0);
    void setB1(const AVector3& b1);
    void setB2(const AVector3& b2);
    void setB3(const AVector3& b3);
    void setColor(const AVector3& color);

    // getters for control points and color
    const AVector3& b0() const;
    const AVector3& b1() const;
    const AVector3& b2() const;
    const AVector3& b3() const;
    const AVector3& color() const;

protected:
    AVector3 _b0;
    AVector3 _b1;
    AVector3 _b2;
    AVector3 _b3;
    AVector3 _color; 
};

class CubicDeCasteljau : public Cubic
{
public:
    CubicDeCasteljau();
    virtual ~CubicDeCasteljau();

    // Implements cubic interpolation using de Casteljau's algorithm
    virtual AVector3 interpolate(double t) const;
};

class CubicBernstein : public Cubic
{
public:
    CubicBernstein();
    virtual ~CubicBernstein();

    // Implements cubic interpolation using bernstein polynomials
    virtual AVector3 interpolate(double t) const;
};