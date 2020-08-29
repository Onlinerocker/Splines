#include <string>
#include "AIKViewer.h"
#include "AMotion.h"
#include "ABVHReader.h"
#include "GL/glew.h"
#include "GL/glut.h"
#include <algorithm>
#include <AntTweakBar.h>
#include <iostream>

AIKViewer::AIKViewer() : 
    mIKChainSize(-1),
    mEpsilon(1.0),
    mMaxIters(50),
    mType(CCD) 
{
}

AIKViewer::~AIKViewer()
{
}

void AIKViewer::initializeGui()
{
    AIKSimple::initializeGui();

    mIKBar = TwNewBar("IK Params");
    TwDefine(" 'IK Params' size='200 200' position='600 5' "
        "iconified=false fontresizable=false alpha=200");
    TwEnumVal ikTypeEV[] =
    {
        { ANALYTIC, "Analytic" },
        { CCD, "CCD" }
    };
    ikType = TwDefineEnum("IKType", ikTypeEV, 2);
    TwAddVarCB(mIKBar, "Type", ikType, onSetIKCb, onGetIKCb, this, " ");
    TwAddButton(mIKBar, "Reset Pose", ResetIKCb, this, " ");
    TwAddVarRW(mIKBar, "Epsilon", TW_TYPE_DOUBLE, &mEpsilon, " ");
    TwAddVarRW(mIKBar, "Max Iterations", TW_TYPE_INT32, &mMaxIters, " ");
    TwAddVarRW(mIKBar, "Chain Length", TW_TYPE_INT32, &mIKChainSize, " ");
}

void AIKViewer::setupCharacter()
{
    AMotion dummy;
    ABVHReader bvhLoader;
    bool v = bvhLoader.load("../motions/Beta/Beta.bvh", mActor, dummy);

    if (v)
    {
        mActor.fk();
        loadIKJoints();
    }
    else
    {
        std::cout << "AIKViewer cannot setup skeleton\n";
    }
}

void AIKViewer::reset()
{
    setupCharacter();
    mSelectedJoint = -1;
    mGoalPosition = AVector3::Zero;
    glutPostRedisplay();
}

void AIKViewer::onSelectIKJoint(int selectedJoint)
{
    mSelectedJoint = selectedJoint;
    mGoalPosition = mActor.getByID(mSelectedJoint)->getGlobalTranslation();
}

void AIKViewer::update() // assumes joint already chosen
{
    if (mSelectedJoint == -1) return;

    //std::cout << mGoalPosition << std::endl;
    mIKController.setEpsilon(mEpsilon);
    if (mType == ANALYTIC) 
    {
        mIKController.solveIKAnalytic(mActor, mSelectedJoint, mGoalPosition);
    }
    else 
    {
        mIKController.solveIKCCD(mActor, mSelectedJoint, 
            mGoalPosition, mIKChainSize, mMaxIters);
    }
}

void TW_CALL AIKViewer::onSetIKCb(const void *value, void *clientData)
{
    AIKViewer* viewer = ((AIKViewer*)clientData);
    IKType v = *(const IKType *)value;  // for instance
    viewer->mType = v;
}

void TW_CALL AIKViewer::onGetIKCb(void *value, void *clientData)
{
    AIKViewer* viewer = ((AIKViewer*)clientData);
    *static_cast<IKType *>(value) = viewer->mType;
}

