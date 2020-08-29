#include "AJoint.h"

void AJoint::fk()
{
    if(mParent == NULL)
    {
        mLocal2Global = mLocal2Parent;
    }
    else
    {
        mLocal2Global = mParent->mLocal2Global * mLocal2Parent;
    }

    for(int x=0; x < mChildren.size(); x++)
    {
        mChildren[x]->fk();
    }
}

