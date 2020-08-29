#ifndef AApp_H_
#define AApp_H_

#include "GL/glew.h"
#include "GL/glut.h"
#include <AntTweakBar.h>
#include <vector>

const int DEFAULT_WINDOW_WIDTH = 800;
const int DEFAULT_WINDOW_HEIGHT = 600;
const int DEFAULT_WINDOW_STARTX = 100;
const int DEFAULT_WINDOW_STARTY = 100;

class ACamera;
class ATimer;
class AFramework;
class AApp
{
public:
    AApp(AFramework* framework);
    virtual ~AApp();

    virtual void init(int argc, char** argv,
        int winwidth = DEFAULT_WINDOW_WIDTH,
        int winheight = DEFAULT_WINDOW_HEIGHT,
        int winstartx = DEFAULT_WINDOW_STARTX,
        int winstarty = DEFAULT_WINDOW_STARTY);
    virtual void run();
    virtual ACamera* getCamera();

    int getHeight() const;
    int getWidth() const;
    double dt() const; // amount of time since last frame
    double elapsedTime() const; // amount of time since start or last reset
    bool getPaused() const;
    void setPaused(bool b);

protected:

    // overridable interface
    virtual void onAppInitializeGui() {}
    virtual void onAppInitializeView() {}
    virtual void onAppMouseMotion(int x, int y) {}
    virtual void onAppMouse(int button, int state, int x, int y) {}
    virtual void onAppKeyboard(unsigned char key, int x, int y) {}
    virtual void onAppKeyboardSpecial(unsigned char key, int x, int y) {}
    virtual void onAppDraw() {}
    virtual void onAppTimer() {}

protected:

    bool initializeOpenGL();
    void initializeGui();

    static void onMouseMotionCb(int x, int y);
    static void onMouseCb(int button, int state, int x, int y);
    static void onKeyboardCb(unsigned char key, int x, int y);
    static void onKeyboardSpecialCb(int key, int x, int y);
    static void onTimerCb(int value);
    static void onMenuCb(int value);
    static void onResizeCb(int width, int height);
    static void onDrawCb();

    void onMouseMotion(int x, int y);
    void onMouse(int button, int state, int x, int y);
    void onKeyboard(unsigned char key, int x, int y);
    void onKeyboardSpecial(int key, int x, int y);
    void onTimer(int value);
    void onMenu(int value);
    void onResize(int width, int height);
    void onDraw();

    static void TW_CALL onCopyStdStringToClient(
        std::string& dest, const std::string& src);

protected:
    AFramework* mFramework;
    ATimer* mClock;
    int mWindowWidth, mWindowHeight;
    double mCurrentTime;
    double mDt;
};

#endif
