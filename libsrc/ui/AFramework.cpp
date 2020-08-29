#include <string>
#include "AFramework.h"
#include "AApp2D.h"
#include "AApp3D.h"
#include <algorithm>

AFramework::AFramework(AFramework::Display type) :
    mApp(0)
{
    if (type == AFramework::Orthographic)
    {
        mApp = new AApp2D(this);
    }
    else
    {
        mApp = new AApp3D(this);
    }
}

AFramework::~AFramework()
{
    delete mApp;
}

void AFramework::init(int argc, char** argv, int winwidth, int winheight, int winstartx, int winstarty)
{
    mApp->init(argc, argv, winwidth, winheight, winstartx, winstarty);
}

void AFramework::run()
{
    mApp->run();
}

int AFramework::getHeight() const
{
    return mApp->getHeight();
}

int AFramework::getWidth() const
{
    return mApp->getWidth();
}

double AFramework::dt() const
{
    return mApp->dt();
}

double AFramework::elapsedTime() const
{
    return mApp->elapsedTime();
}

ACamera* AFramework::getCamera()
{
    return mApp->getCamera();
}

