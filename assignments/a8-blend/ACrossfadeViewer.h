#pragma once

#include "AFramework.h"
#include "AUiTimeBar.h"
#include "ASkeletonDrawer.h"
#include "AnimationToolkit.h"
#include "AGLObjects.h" 

class ACrossfadeViewer : public AFramework
{
public:
    ACrossfadeViewer();
    virtual ~ACrossfadeViewer();
    void loadMotion1(const std::string& filename);
    void loadMotion2(const std::string& filename);
    void blend(int start1, int start2, int numBlendFrames);
    void blend();
    void draw();
    void update();

protected:

    void initializeGui();
    void onLoadMotion1();
    void onLoadMotion2();

    static void TW_CALL onBlendCb(void *clientData);
    static void TW_CALL onLoadMotion1Cb(void *clientData);
    static void TW_CALL onLoadMotion2Cb(void *clientData);

protected:
    std::string mFilename;
    std::string mFilename1;
    std::string mFilename2;
    int mNumKeys1;
    int mNumKeys2;
    int mNumKeys;
    AMotionBlender mMotionBlender;
    ASkeletonDrawer mDrawer;
    ASkeleton mSkeleton;
    AMotion mMotion1;
    AMotion mMotion2;
    AMotion mBlend;

    AVector3 leftFootPos;
    AVector3 rightFootPos;

    bool leftOnGround;
    bool rightOnGround;

    TwBar *mBlendBar;
    int mMotionKeyId1;
    int mMotionKeyId2;
    int mNumBlendKeys;

    AUiTimeBar mPlayerBar;
};
