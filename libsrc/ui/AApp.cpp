#include <string>
#include "AApp.h"
#include "AFramework.h"
#include "AOsUtils.h"
#include "ATimer.h"
#include <algorithm>

static AApp* theInstance = 0;

AApp::AApp(AFramework* framework) :
    mFramework(framework),
    mCurrentTime(0),
    mDt(0)
{
    mClock = new ATimer();
}

AApp::~AApp()
{
    delete mClock;
    TwTerminate();
}

void AApp::init(int argc, char** argv, int winwidth, int winheight, int winstartx, int winstarty)
{
    mWindowWidth = winwidth;
    mWindowHeight = winheight;

    theInstance = this;
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_MULTISAMPLE);
    glutInitWindowSize(winwidth, winheight);
    glutInitWindowPosition(winstartx, winstarty);
    glutCreateWindow("Basic Viewer");

    initializeOpenGL();

    glutDisplayFunc(AApp::onDrawCb);
    glutKeyboardFunc(AApp::onKeyboardCb);
    glutSpecialFunc(AApp::onKeyboardSpecialCb);
    glutMouseFunc(AApp::onMouseCb);
    glutMotionFunc(AApp::onMouseMotionCb);
    glutTimerFunc(100, AApp::onTimerCb, 0);
    glutReshapeFunc(AApp::onResizeCb);

    initializeGui();
    onAppInitializeView();

    mFramework->setup(); // user init
}

bool AApp::initializeOpenGL()
{
    // Initialize GLEW.
    GLenum lError = glewInit();
    if (lError != GLEW_OK)
    {
    	return false;
    }

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glClearColor(0.8, 0.8, 0.8, 1.0);

    // OpenGL 1.5 at least.
    if (!GLEW_VERSION_1_5)
    {
    	std::cout << "The OpenGL version should be at least 1.5 "
            "to display shaded scene! (version = \n";
    	return false;
    }

    glEnable(GL_BLEND);
    glEnable(GL_ALPHA_TEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glShadeModel(GL_SMOOTH);

    glEnable(GL_NORMALIZE);
    glDisable(GL_LIGHTING);
    glCullFace(GL_BACK);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    glClearStencil(0); //clear the stencil buffer
    glClearDepth(1.0f);

    glEnable(GL_MULTISAMPLE_ARB);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
    glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_POLYGON_SMOOTH);
    glEnable(GL_MULTISAMPLE);

    return true;
}

void AApp::initializeGui()
{
    glutPassiveMotionFunc((GLUTmousemotionfun)TwEventMouseMotionGLUT);
    TwGLUTModifiersFunc(glutGetModifiers);
    TwInit(TW_OPENGL, NULL);
    TwWindowSize(mWindowWidth, mWindowHeight);

    TwCopyStdStringToClientFunc(onCopyStdStringToClient);

    onAppInitializeGui();
    mFramework->initializeGui();
}

void AApp::run()
{
    glutMainLoop();
}

void AApp::onMouseMotionCb(int x, int y)
{
    theInstance->onMouseMotion(x, y);
}

void AApp::onMouseMotion(int pX, int pY)
{
    // Check GUI first
    if (TwEventMouseMotionGLUT(pX, pY)) return;

    // call specialized subclass
    onAppMouseMotion(pX, pY);

    // call framework
    mFramework->mouseMove(pX, pY); // user hook

    // redraw
    glutPostRedisplay();
}

void AApp::onMouseCb(int button, int state, int x, int y)
{
    theInstance->onMouse(button, state, x, y);
}
void AApp::onMouse(int pButton, int pState, int pX, int pY)
{
    // Check GUI first
    if (TwEventMouseButtonGLUT(pButton, pState, pX, pY))  return;

    onAppMouse(pButton, pState, pX, pY);
    mFramework->mousePress(pButton, glutGetModifiers(), pX, pY);
    onMouseMotionCb(pX, pY);
}

void AApp::onKeyboardSpecialCb(int key, int x, int y)
{
    theInstance->onKeyboardSpecial(key, x, y);
}
void AApp::onKeyboardSpecial(int key, int x, int y)
{
    TwEventSpecialGLUT(key, x, y);
    onAppKeyboardSpecial(key, x, y);
    mFramework->keyPress('\0', key, x, y);
}

double AApp::dt() const
{
    return mDt;
}

double AApp::elapsedTime() const
{
    return mCurrentTime;
}

void AApp::onTimerCb(int value)
{
    theInstance->onTimer(value);
}

void AApp::onTimer(int value)
{
    // Loop in the animation stack if not paused.
    mDt = mClock->totalElapsedTime();
    mClock->restart();
    mCurrentTime = mCurrentTime + mDt;

    mFramework->update(); // user function

    // Call the timer to display the next frame.    
    glutTimerFunc(10, onTimerCb, 0);

    // Must call this everytime so that GUI displays
    glutPostRedisplay();
    onAppTimer();
}

void AApp::onKeyboardCb(unsigned char key, int x, int y)
{
    theInstance->onKeyboard(key, x, y);
}

void AApp::onKeyboard(unsigned char pKey, int x, int y)
{
    // Exit on ESC key.
    if (pKey == 27)
    {
    	exit(0);
    }

    if (TwEventKeyboardGLUT(pKey, x, y)) return;

    onAppKeyboard(pKey, x, y);
    mFramework->keyPress(pKey, 0, x, y);
}

void AApp::onMenuCb(int value)
{
    theInstance->onMenu(value);
}
void AApp::onMenu(int value)
{
    switch (value)
    {
    case -1: exit(0);
    default: onKeyboardCb(value, 0, 0); break;
    }
}

void AApp::onResizeCb(int width, int height)
{
    theInstance->onResize(width, height);
}
void AApp::onResize(int width, int height)
{
    glViewport(0, 0, (GLsizei)width, (GLsizei)height);
    mWindowWidth = width;
    mWindowHeight = height;
    TwWindowSize(width, height);
}

void AApp::onDrawCb()
{
    theInstance->onDraw();
}

void AApp::onDraw()
{
    onAppDraw();
    mFramework->draw();
    TwDraw();
    glutSwapBuffers();
}

void TW_CALL AApp::onCopyStdStringToClient(std::string& dest, const std::string& src)
{
    dest = src;
}

int AApp::getHeight() const
{
    return mWindowHeight;
}

int AApp::getWidth() const
{
    return mWindowWidth;
}

ACamera* AApp::getCamera() 
{
    return 0;
}
