#ifndef ACurveEditor_H_
#define ACurveEditor_H_

#include "AFramework.h"
#include "GL/glew.h"
#include "GL/glut.h"
#include <AntTweakBar.h>
#include "AnimationToolkit.h"

class ACurveEditor : public AFramework
{
public:
    ACurveEditor();
    virtual ~ACurveEditor();

protected:

    virtual void initializeGui();
    virtual void draw();
    virtual void update();
    void drawCurve();
    void drawCircle(const AVector3& p); 
    bool hasControlPoints() const;

    virtual void mouseMove(int x, int y);
    virtual void mousePress(int button, int state, int x, int y);
    virtual void keyPress(unsigned char key, int specialKey, int x, int y);
    virtual void addPoint(int x, int y);
    virtual void deletePoint(int x, int y);
    virtual void pickPoint(int x, int y);
    virtual void movePicked(int x, int y);

    static void TW_CALL onClearCb(void* usr);
    static void TW_CALL onSetStyleCb(const void *value, void *clientData);
    static void TW_CALL onGetStyleCb(void *value, void *clientData);

protected:

    ASpline mSpline;
    AVector3 mDot;
    int mRadius;
    int mSelected;
    int mPickType;
    int mButtonState;
    int mModifierState;

    TwBar *mCurveBar;
    TwType curveType;
    TwType modeType;
    enum Mode { ADD, EDIT, REMOVE } mMode;
    bool mShowControlPoints;
};

#endif
