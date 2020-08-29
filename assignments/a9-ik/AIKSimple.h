#ifndef IKSimple_H_
#define IKSimple_H_

#include <string>
#include "AFramework.h"
#include "ASkeletonDrawer.h"
#include "AnimationToolkit.h"

class AIKSimple : public AFramework
{
public:
    AIKSimple();
    virtual ~AIKSimple();
    virtual void setupCharacter();

    void setGoalPosition(const AVector3& pos);
    AVector3 getSelectedPosition() const;

    void setSelectedJoint(const std::string& name);
    std::string getSelectedJoint() const;

protected:

    virtual void initializeGui();
    virtual void draw();
    virtual void drawOverlay();
    virtual void loadIKJoints();
    virtual void update();
    virtual void reset();
    virtual void mouseMove(int pX, int pY);
    virtual void mousePress(int button, int state, int x, int y);
    virtual void onSelectIKJoint(int selectedJoint) {}

    static void TW_CALL ResetIKCb(void* clientData);
    static void TW_CALL SelectIKCb(void* clientData);
    static void TW_CALL onSetGoalXCb(const void *value, void *clientData);
    static void TW_CALL onGetGoalXCb(void *value, void *clientData);
    static void TW_CALL onSetGoalYCb(const void *value, void *clientData);
    static void TW_CALL onGetGoalYCb(void *value, void *clientData);
    static void TW_CALL onSetGoalZCb(const void *value, void *clientData);
    static void TW_CALL onGetGoalZCb(void *value, void *clientData);

protected:
    ASkeleton mActor;
    AIKController mController;
    ASkeletonDrawer mDrawer;
    AVector3 mGoalPosition;
    int mSelectedJoint;
    bool mSelectedRecticle;
    int mLastX, mLastY, mLastIKX, mLastIKY, mModifierState, mButtonState;

    TwBar *mPoseEditBar;
    struct EffectorData { AIKSimple* viewer; int jointid; std::string name; };
    std::vector<EffectorData*> mEffectorData;

};

#endif
