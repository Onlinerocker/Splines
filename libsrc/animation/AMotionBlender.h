#ifndef MotionBlender_h_
#define MotionBlender_h_

#include "AMotion.h"
#include "ASkeleton.h"

class AMotionBlender
{
public:
    AMotionBlender() {}
    virtual ~AMotionBlender() {}

    void blend(AMotion& motion1, AMotion& motion2, 
        int startFrame, int endFrame, int numBlendFrames, AMotion& blend);

    void append(AMotion& input, 
        int startKeyId, int endKeyId, AMotion& output);

    void align(AMotion& motion1, AMotion& motion2,
        int startKeyId, int endKeyId, int numBlendFrames);

    void crossfade(AMotion& motion1, AMotion& motion2,
        int startKeyId, int endKeyId, int numBlendFrames, AMotion& blend);
};

#endif
