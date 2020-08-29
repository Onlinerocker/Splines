#include <string>
#include "ACrossfadeViewer.h"
#include "AOsUtils.h"
#include "ABVHReader.h"
#include "GL/glew.h"
#include "GL/glut.h"
#include <algorithm>
#include <AntTweakBar.h>

ACrossfadeViewer::ACrossfadeViewer() : 
   AFramework(AFramework::Perspective),
   mFilename("Blend"),
   mFilename1(""),
   mFilename2(""),
   mNumKeys1(0), 
   mNumKeys2(0), 
   mNumKeys(0),
   mMotionKeyId1(0), 
   mMotionKeyId2(0), 
   mNumBlendKeys(10)
{
    leftOnGround = false;
    rightOnGround = false;
}

ACrossfadeViewer::~ACrossfadeViewer()
{
}

void ACrossfadeViewer::loadMotion1(const std::string& filename)
{
    ABVHReader reader;
    reader.load(filename, mSkeleton, mMotion1);

    mNumKeys1 = mMotion1.getNumKeys();
    mFilename1 = PruneName(filename);
    mMotionKeyId1 = mNumKeys1-mNumBlendKeys;
    mNumKeys = mBlend.getNumKeys();
}

void ACrossfadeViewer::loadMotion2(const std::string& filename)
{
    ABVHReader reader;
    reader.load(filename, mSkeleton, mMotion2);

    mNumKeys2 = mMotion2.getNumKeys();
    mFilename2 = PruneName(filename);
    mMotionKeyId2 = 0;
    mNumKeys = mBlend.getNumKeys();
}

void ACrossfadeViewer::onLoadMotion1()
{
    std::string filename = PromptToLoad();
    loadMotion1(filename);
}

void ACrossfadeViewer::onLoadMotion2()
{
    std::string filename = PromptToLoad();
    loadMotion2(filename);
}

void ACrossfadeViewer::blend(int start1, int start2, int numBlendFrames)
{
    mMotionKeyId1 = start1;
    mMotionKeyId2 = start2;
    mNumBlendKeys = numBlendFrames;
    blend();
}

void ACrossfadeViewer::blend()
{
    std::cout << "BLEND " << mMotionKeyId1 << " " << 
		  mMotionKeyId2 << " " << mNumBlendKeys << std::endl;

    mMotionBlender.blend(mMotion1, mMotion2, 
        mMotionKeyId1, mMotionKeyId2, mNumBlendKeys, mBlend);

    mNumKeys = mBlend.getNumKeys();
}

void ACrossfadeViewer::initializeGui()
{
    mPlayerBar.initialize();

    mBlendBar = TwNewBar("Blend controls");
    TwDefine(" 'Blend controls' size='200 250' position='5 185' "
        "iconified=false fontresizable=false alpha=200");
    TwAddVarRO(mBlendBar, "Motion 1", TW_TYPE_STDSTRING, &mFilename1, "");
    TwAddVarRO(mBlendBar, "NumKeys 1", TW_TYPE_INT32, &mNumKeys1, "");
    TwAddButton(mBlendBar, "LoadMotion1Btn", onLoadMotion1Cb, this, 
        " label='Load Motion1'");
    TwAddSeparator(mBlendBar, NULL, "");
    TwAddVarRO(mBlendBar, "Motion 2", TW_TYPE_STDSTRING, &mFilename2, "");
    TwAddVarRO(mBlendBar, "Duration 2", TW_TYPE_INT32, &mNumKeys2, "");
    TwAddButton(mBlendBar, "LoadMotion2Btn", onLoadMotion2Cb, this, 
        " label='Load Motion2'");
    TwAddSeparator(mBlendBar, NULL, "");
    TwAddVarRW(mBlendBar, "Key 1", TW_TYPE_INT32, &mMotionKeyId1, 
        " group='Blend'");
    TwAddVarRW(mBlendBar, "Key 2", TW_TYPE_INT32, &mMotionKeyId2, 
        " group='Blend'");
    TwAddVarRW(mBlendBar, "Num Keys", TW_TYPE_INT32, &mNumBlendKeys, 
        " group='Blend'");
    TwAddButton(mBlendBar, "BlendBtn", onBlendCb, this, 
        " label='Blend' group='Blend'");
}

void ACrossfadeViewer::update()
{
    leftFootPos = mSkeleton.getByName("Beta:LeftToeBase")->getGlobalTranslation();
    rightFootPos = mSkeleton.getByName("Beta:RightToeBase")->getGlobalTranslation();

    leftOnGround = (leftFootPos[1] <= 3);
    rightOnGround = (rightFootPos[1] <= 3);

    bool paused = mPlayerBar.paused;
    if (!paused)
    {
        mPlayerBar.currentTime += dt() * mPlayerBar.timeScale;
        mPlayerBar.currentFrame = mBlend.getKeyID(mPlayerBar.currentTime);
    }
    else
    {
        mPlayerBar.currentFrame = 
            mPlayerBar.currentFrame % mBlend.getNumKeys();

        mPlayerBar.currentTime = 
            mPlayerBar.currentFrame * mBlend.getDeltaTime();
    }

    mBlend.update(mSkeleton, mPlayerBar.currentTime);
    mPlayerBar.refresh();
}

void ACrossfadeViewer::draw()
{
    mDrawer.draw(mSkeleton);

    ASetMaterial(AVector3(1,0,0));
    if(leftOnGround) ADrawCube(leftFootPos, AMatrix3::Identity, AVector3(10,10,10));
    if(rightOnGround) ADrawCube(rightFootPos, AMatrix3::Identity, AVector3(10,10,10));
}

void TW_CALL ACrossfadeViewer::onBlendCb(void *usrData)
{
    ((ACrossfadeViewer*)usrData)->blend();
}

void TW_CALL ACrossfadeViewer::onLoadMotion1Cb(void *usrData)
{
    ((ACrossfadeViewer*)usrData)->onLoadMotion1();
}

void TW_CALL ACrossfadeViewer::onLoadMotion2Cb(void *usrData)
{
    ((ACrossfadeViewer*)usrData)->onLoadMotion2();
}

