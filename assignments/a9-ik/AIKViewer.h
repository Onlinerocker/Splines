#ifndef IKViewer_H_
#define IKViewer_H_

#include <string>
#include "AIKSimple.h"
#include "AnimationToolkit.h"

class AIKViewer : public AIKSimple
{
public:
    AIKViewer();
    virtual ~AIKViewer();
    virtual void setupCharacter();

protected:

    virtual void initializeGui();
    virtual void reset();
    virtual void update();
    virtual void onSelectIKJoint(int selectedJoint);

    static void TW_CALL onGetIKCb(void *value, void *clientData);
    static void TW_CALL onSetIKCb(const void *value, void *clientData);

protected:
    AIKController mIKController;
    int mIKChainSize;
    double mEpsilon;
    int mMaxIters;
    enum IKType { ANALYTIC, CCD } mType;
    TwType ikType;
    TwBar* mIKBar;
};

#endif
