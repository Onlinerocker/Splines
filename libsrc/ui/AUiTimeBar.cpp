#include <string>
#include "AUiTimeBar.h"
#include "AOsUtils.h"
#include <algorithm>

AUiTimeBar::AUiTimeBar() :
    paused(false),
    currentFrame(0),
    currentTime(0.0),
    timeScale(1.0)
{
}

AUiTimeBar::~AUiTimeBar()
{
}

void AUiTimeBar::initialize()
{
    char buff[1024];
    sprintf(buff, " min='%d' max='%d' step=0.1", 0, 100);

    mPlayerBar = TwNewBar("Time controls");
    TwDefine(" 'Time controls' size='200 175' position='5 5' "
        "iconified=false fontresizable=false alpha=200");

    TwAddButton(mPlayerBar, "PlayBtn", onPlayCb, this, 
        paused ? " label='Play'" : " label='Pause'");

    TwAddVarCB(mPlayerBar, "Frame", TW_TYPE_INT32, 
        onSetFrameCb, onGetFrameCb, this, " step=1");

    TwAddVarCB(mPlayerBar, "Time", TW_TYPE_DOUBLE, 
        onSetTimeCb, onGetTimeCb, this, " step=0.1 precision=2");

    TwAddVarRW(mPlayerBar, "Time scale", TW_TYPE_DOUBLE, &timeScale, "");

    //TwAddVarRW(mPlayerBar, "Model", TW_TYPE_STDSTRING, &mModel, "");
}

void AUiTimeBar::refresh()
{
    TwRefreshBar(mPlayerBar);
}

void TW_CALL AUiTimeBar::onPlayCb(void* usr)
{
    AUiTimeBar* viewer = ((AUiTimeBar*)usr);
    viewer->paused = !viewer->paused;

    if (viewer->paused) 
    {
        TwSetParam(viewer->mPlayerBar, "PlayBtn", "label", 
            TW_PARAM_CSTRING, 1, "Play");
    }
    else 
    {
        TwSetParam(viewer->mPlayerBar, "PlayBtn", "label", 
            TW_PARAM_CSTRING, 1, "Pause");
    }
}

void TW_CALL AUiTimeBar::onSetFrameCb(const void *value, void *clientData)
{
    AUiTimeBar* viewer = ((AUiTimeBar*)clientData);
    int v = *(const int *) value;  // for instance
    viewer->currentFrame = v;
}

void TW_CALL AUiTimeBar::onGetFrameCb(void *value, void *clientData)
{
    AUiTimeBar* viewer = ((AUiTimeBar*)clientData);
    *static_cast<int *>(value) = viewer->currentFrame;
}

void TW_CALL AUiTimeBar::onSetTimeCb(const void *value, void *clientData)
{
    AUiTimeBar* viewer = ((AUiTimeBar*)clientData);
    double v = *(const double *) value;  // for instance
    v = std::max<double>(0, v);
    viewer->currentTime = v;
    //std::cout << "SET FRAME BUTTON PRESSED " << v << " " << std::endl;
}

void TW_CALL AUiTimeBar::onGetTimeCb(void *value, void *clientData)
{
    AUiTimeBar* viewer = ((AUiTimeBar*)clientData);
    *static_cast<double *>(value) = viewer->currentTime;
}

