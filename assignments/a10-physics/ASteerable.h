#ifndef STEERINGCHARACTER_H_
#define STEERINGCHARACTER_H_

#include "ASkeletonDrawer.h"
#include "ASkeleton.h"
#include "AMotion.h"

class ASteerable
{
public:
   ASteerable();
   virtual ~ASteerable();
   bool operator==(const ASteerable& other) const;

   void reset();
   void reset(const AVector3& pos);
   void update(const AVector3& desiredVelocity, double dt);
   void draw();

   AVector3 getPosition() const;
   AVector3 getVelocity() const;

protected:
   int _id;
   AVector3 _position;
   AVector3 _desiredVelocity;
   ASkeleton _skeleton;
   AMotion _walk;
   AMotion _idle;
   double _time;
};

#endif
