#ifndef AFramework_H_
#define AFramework_H_

#ifdef _WIN32
#include <Windows.h>
#endif
#include "GL/glew.h"
#include "GL/glut.h"
#include "AApp.h"
#include <AntTweakBar.h>
#include <vector>

class ACamera;
class AFramework
{
public:
    enum Display { Orthographic, Perspective };
    AFramework(Display type);
    virtual ~AFramework();

    // Public interface
    // Usage:
    // int main(int argc, char** argc)
    // {
    //    AFramework viewer(AFramework::2D);
    //    viewer.init(argc, argv);
    //    viewer.run();
    //    return 0;
    // }
    void init(int argc, char** argv,
        int winwidth = DEFAULT_WINDOW_WIDTH,
        int winheight = DEFAULT_WINDOW_HEIGHT,
        int winstartx = DEFAULT_WINDOW_STARTX,
        int winstarty = DEFAULT_WINDOW_STARTY);
    void run();

    // overridable user interface
    virtual void setup() {}
    virtual void update() {}
    virtual void draw() {}
    virtual void initializeGui() {}
    virtual void mouseMove(int x, int y) {}
    virtual void mousePress(int button, int state, int x, int y) {}
    virtual void keyPress(unsigned char key, int specialKey, int x, int y) {}
    double dt() const; // amount of time since last frame
    double elapsedTime() const; // amount of time since start (can be reset to zero)

protected:
    int getHeight() const;
    int getWidth() const;
    ACamera* getCamera();

protected:
    AApp* mApp; 
};

#endif
