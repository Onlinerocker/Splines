#ifndef ACYCLOPS_H_
#define ACYCLOPS_H_

#include "ASkeletonDrawer.h"

class ACyclops : public ASkeletonDrawer 
{
public:
	ACyclops();
	virtual ~ACyclops();
   virtual void draw(const ASkeleton& skeleton);

protected:
   virtual void drawBodyParts(AJoint* currentJoint);
};

#endif
