#ifndef MrFancy_H_
#define MrFancy_H_

#include "AGLObjects.h"
#include "ASkeletonDrawer.h"

class AMrFancy : public ASkeletonDrawer
{
public:
	AMrFancy()
   {
      setShowAxis(true);
   }

	virtual ~AMrFancy()
   {
   }

   void drawBodyParts(AJoint* currentJoint)
   {
      ASkeletonDrawer::drawBodyParts(currentJoint);
       // draw monocle and hat
       if (currentJoint->getName() == "Beta:HeadSite")
       {
       }
   }
};

#endif
