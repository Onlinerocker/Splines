#ifndef BVHREADER_H_
#define BVHREADER_H_

#include <map>
#include <string>
#include <fstream>
#include "ASkeleton.h"
#include "AMotion.h"

class ABVHReader
{
public:
    ABVHReader();
    virtual ~ABVHReader();

    bool load(const std::string& filename,
        ASkeleton& skeleton, AMotion& motion) const;

protected:

    AQuaternion computeBVHRot(float r1, float r2, float r3, 
        const std::string& rotOrder) const;

    bool loadSkeleton(std::ifstream &inFile, ASkeleton& skeleton) const;

    bool loadJoint(std::ifstream &inFile, ASkeleton& skeleton, 
        AJoint *pParent, std::string prefix) const;

    bool loadMotion(std::ifstream &inFile, 
        ASkeleton& skeleton, AMotion& motion) const;

    void loadFrame(std::ifstream& inFile, 
        ASkeleton& skeleton, AMotion& motion) const;
};

#endif
