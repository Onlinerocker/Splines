#include <string>
#include "AApp2D.h"
#include <algorithm>

using namespace std;

AApp2D::AApp2D(AFramework* framework) :
    AApp(framework)
{
}

AApp2D::~AApp2D()
{
}

void AApp2D::onAppInitializeView()
{
    glClearColor(0.0, 0.0, 0.0, 1.0);
}

void AApp2D::onAppDraw()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, mWindowWidth, 0, mWindowHeight, -1000, 1000);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

