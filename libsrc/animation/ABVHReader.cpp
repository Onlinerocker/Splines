#include "ABVHReader.h"
#include "AVector3.h"
#include "AMatrix3.h"
#include "AQuaternion.h"
#include <iostream>
#include <GL/glut.h>

ABVHReader::ABVHReader() 
{

}

ABVHReader::~ABVHReader()
{
}

bool ABVHReader::load(const std::string& filename,
    ASkeleton& skeleton, AMotion& motion) const
{
    std::ifstream inFile(filename.c_str());
    if (!inFile.is_open())
    {
        std::cout << "WARNING: Could not open " << filename.c_str() << std::endl;
        return false;
    }

    skeleton.clear();
    motion.clear();

    bool status = loadSkeleton(inFile, skeleton);
    status = status && loadMotion(inFile, skeleton, motion);
    inFile.close();
    return status;
}

bool ABVHReader::loadSkeleton(std::ifstream& inFile, ASkeleton& skeleton) const
{
    AVector3 offsets;
    std::string readString, jointname;
    int channelCount;

    inFile >> readString;
    if (readString != "HIERARCHY")
        return false;
    inFile >> readString;
    if (readString != "ROOT" && readString != "JOINT")
        return false;
    inFile.get(); //" "
    getline(inFile, jointname);// joint name
    AJoint* joint = new AJoint(jointname);
    skeleton.addJoint(joint);
    inFile >> readString; // "{"
    inFile >> readString; // "OFFSET"
    inFile >> offsets[0] >> offsets[1] >> offsets[2];
    joint->setLocalTranslation(offsets);
    inFile >> readString;
    if (readString != "CHANNELS")
        return false;
    inFile >> channelCount;
    joint->setNumChannels(channelCount);
    getline(inFile, readString);	// " Xposition Yposition Zposition Zrotation Xrotation Yrotation"
    joint->setRotationOrder(readString);
    inFile >> readString;
    while (readString != "}")
    {
        if (!loadJoint(inFile, skeleton, joint, readString))
        {
            return false;
        }
        inFile >> readString;
    }
    if (readString != "}") return false;

    skeleton.fk();
    return true;
}

bool ABVHReader::loadJoint(std::ifstream &inFile, 
    ASkeleton& skeleton, AJoint *pParent, std::string prefix) const
{
    std::string readString, jointname;
    AVector3 offsets;
    int channelCount;
    if (prefix == "JOINT")
    {
        inFile.get(); //" "
        getline(inFile, jointname);// joint name
        AJoint* joint = new AJoint(jointname);
        skeleton.addJoint(joint, pParent);
        inFile >> readString; // "{"
        inFile >> readString; // "OFFSET"
        inFile >> offsets[0] >> offsets[1] >> offsets[2];
        joint->setLocalTranslation(offsets);
        inFile >> readString; // "CHANNELS"
        inFile >> channelCount;
        joint->setNumChannels(channelCount);

        getline(inFile, readString);// " Zrotation Xrotation Yrotation"
        joint->setRotationOrder(readString);

        inFile >> readString; // "Joint" or "}" or "End"
        while (readString != "}")
        {
            if (loadJoint(inFile, skeleton, joint, readString) == false)
                return false;
            inFile >> readString; // "Joint" or "}" or "End"
        }
        return true;
    }
    else if (prefix == "End")
    {
        inFile.get(); //" "
        getline(inFile, jointname);// joint name
        if (jointname.find("Site") != std::string::npos)
        {
            jointname = pParent->getName() + "Site";
        }

        AJoint* joint = new AJoint(jointname);
        joint->setNumChannels(0);
        skeleton.addJoint(joint, pParent);
        inFile >> readString; // "{"
        inFile >> readString; // "OFFSET"
        inFile >> offsets[0] >> offsets[1] >> offsets[2];
        joint->setLocalTranslation(offsets);
        inFile >> readString; // "}"
        return true;
    }
    else return false;
}

bool ABVHReader::loadMotion(std::ifstream& inFile, 
    ASkeleton& skeleton, AMotion& motion) const
{
    std::string readString;
    int frameCount;
    inFile >> readString;
    if (readString != "MOTION")
        return false;
    inFile >> readString;
    if (readString != "Frames:")
        return false;
    inFile >> frameCount;
    inFile >> readString; // "Frame"
    getline(inFile, readString); // " Time: 0.033333"
    float dt = atof(&(readString.c_str()[6]));

    motion.setFramerate(1.0/dt);

    // Read frames
    for (int i = 0; i < frameCount; i++)
    {
       loadFrame(inFile, skeleton, motion);
    }

    return true;
}

void ABVHReader::loadFrame(std::ifstream& inFile, 
    ASkeleton& skeleton, AMotion& motion) const
{
    float tx, ty, tz, r1, r2, r3;
    APose pose;
    for (int i = 0; i < skeleton.getNumJoints(); i++)
    {
        tx = ty = tz = 0.0f;
        r1 = r2 = r3 = 0.0f;

        AJoint* pJoint = skeleton.getByID(i);
        if (pJoint->getNumChannels() == 6)
        {
            inFile >> tx >> ty >> tz;
            inFile >> r1 >> r2 >> r3;
        }
        else if (pJoint->getNumChannels() == 3)
        {
            inFile >> r1 >> r2 >> r3;
        }
        else
        {
        }

        if (i == 0) // root joint
        {
            pose.rootPos = AVector3(tx, ty, tz); 
        }

        AQuaternion quat = computeBVHRot(r1, r2, r3, pJoint->getRotationOrder());
        pose.jointRots.push_back(quat);
    }
    motion.appendKey(pose);
}

AQuaternion ABVHReader::computeBVHRot(float r1, float r2, float r3, 
    const std::string& rotOrder) const
{
    AMatrix3 m;
    float ry, rx, rz;

    if (rotOrder == "xyz")
    {
        rx = r1; ry = r2; rz = r3;
        m.fromEulerAnglesXYZ(AVector3(rx, ry, rz) * ADeg2Rad);
    }
    else if (rotOrder == "xzy")
    {
        rx = r1; rz = r2; ry = r3;
        m.fromEulerAnglesXZY(AVector3(rx, ry, rz) * ADeg2Rad);
    }
    else if (rotOrder == "yxz")
    {
        ry = r1; rx = r2; rz = r3;
        m.fromEulerAnglesYXZ(AVector3(rx, ry, rz) * ADeg2Rad);
    }
    else if (rotOrder == "yzx")
    {
        ry = r1; rz = r2; rx = r3;
        m.fromEulerAnglesYZX(AVector3(rx, ry, rz) * ADeg2Rad);
    }
    else if (rotOrder == "zxy")
    {
        rz = r1; rx = r2; ry = r3;
        m.fromEulerAnglesZXY(AVector3(rx, ry, rz) * ADeg2Rad);
    }
    else if (rotOrder == "zyx")
    {
        rz = r1; ry = r2; rx = r3;
        m.fromEulerAnglesZYX(AVector3(rx, ry, rz) * ADeg2Rad);
    }
    return m.toQuaternion();
}
