#include "ASteerable.h"
#include "ABehaviors.h"
#include "ABVHReader.h"
#include "AGLObjects.h"

static int counter = 0; // for assigning unique ids

ASteerable::ASteerable() :
   _id(counter++) , _time(0)
{
}

ASteerable::~ASteerable()
{
}

bool ASteerable::operator==(const ASteerable& other) const
{
   return other._id == _id;
}

void ASteerable::reset()
{
   reset(_position);
}

void ASteerable::reset(const AVector3& pos)
{
   _position = pos;
   _desiredVelocity = AVector3::Zero;
}

void ASteerable::update(const AVector3& desiredVelocity, double dt)
{
   _desiredVelocity = desiredVelocity;
   _position = _position + _desiredVelocity * dt;
   _time += dt;
}

void ASteerable::draw()
{
   glDisable(GL_LIGHTING);

   // todo: draw coordinate axes
   AQuaternion q(AVector3(0,1,0), 0);
   AVector3 gx = q * AVector3(1,0,0);
   AVector3 gy = q * AVector3(0,1,0);
   AVector3 gz = q * AVector3(0,0,1);

   AVector3 p = _position;
   ASetColor(AVector3(1,0,0));
   ADrawLine(p, p + 50 * gx);
   ASetColor(AVector3(0,1,0));
   ADrawLine(p, p + 50 * gy);
   ASetColor(AVector3(0,0,1));
   ADrawLine(p, p + 50 * gz);

   glEnable(GL_LIGHTING);

   ASetMaterial(AVector3(0,0,1));
   ADrawSphere(_position, 10);
}

AVector3 ASteerable::getPosition() const
{
   return _position;
}

AVector3 ASteerable::getVelocity() const
{
   return _desiredVelocity;
}
