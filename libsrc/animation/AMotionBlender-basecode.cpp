#include "AMotionBlender.h"
#include <algorithm>

void AMotionBlender::append(AMotion& input, 
    int startKeyId, int endKeyId, AMotion& output)
{
    for(int x=startKeyId; x<endKeyId; x++)
    {
        output.appendKey(input.getKey(x));
    }
}

void AMotionBlender::align(AMotion& motion1, AMotion& motion2, 
    int startKeyId, int endKeyId, int numBlendFrames)
{
    APose pose = motion2.getKey(endKeyId); //pose we want to change

    AQuaternion quat = motion1.getKey(startKeyId).jointRots[0]; //angle we want
    AVector3 pos = motion1.getKey(startKeyId).rootPos; //pos we want

    AVector3 offset = pos - pose.rootPos;
    AQuaternion quatOffset = quat * pose.jointRots[0].inverse();

    ATransform transOffset = ATransform(quatOffset, offset);

    for(int x=0; x < numBlendFrames; x++)
    {      
        pose = motion2.getKey(endKeyId + x);

        ATransform newTrans = transOffset * ATransform(pose.jointRots[0], pose.rootPos);

        pose.rootPos = newTrans.translation;        
        pose.jointRots[0] = newTrans.rotation;

        motion2.editKey(endKeyId + x, pose);
    }
}

void AMotionBlender::crossfade(AMotion& motion1, AMotion& motion2,
    int startKeyId, int endKeyId, int numBlendFrames, AMotion& blend)
{
    APose pose1 = motion1.getKey(startKeyId);
    APose pose2 = motion2.getKey(endKeyId);

    for(float x=0; x<numBlendFrames; x++)
    {
        float alpha = x / numBlendFrames;
        blend.appendKey(APose::Lerp(pose1, pose2, alpha));
    }

}

void AMotionBlender::blend(AMotion& motion1, AMotion& motion2,
    int startKeyId, int endKeyId, int numBlendFrames, AMotion& blend)
{
    if (startKeyId >= motion1.getNumKeys())
    {
        std::cout << "Invalid start key for motion 1" << 
            startKeyId << std::endl;
        return;
    }

    if (endKeyId >= motion2.getNumKeys())
    {
        std::cout << "Invalid end key for motion 2" << 
            startKeyId << std::endl;
        return;
    }

    if (startKeyId + numBlendFrames > motion1.getNumKeys())
    {
        std::cout << "Not enough frames for blending\n";
        numBlendFrames = motion1.getNumKeys() - startKeyId;
    }

    if (endKeyId + numBlendFrames > motion2.getNumKeys())
    {
        std::cout << "Not enough frames for blending\n";
        numBlendFrames = motion2.getNumKeys() - endKeyId;
    }

    if (numBlendFrames <= 0) return;

    blend.clear();
    blend.setFramerate(motion1.getFramerate());

    append(motion1, 0, startKeyId, blend);
    align(motion1, motion2, startKeyId, 0, motion2.getNumKeys());
    crossfade(motion1, motion2, startKeyId, endKeyId, numBlendFrames, blend);
    append(motion2, endKeyId, motion2.getNumKeys(), blend);

}
