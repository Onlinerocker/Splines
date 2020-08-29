#ifndef AUITIMEBAR_H_
#define AUITIMEBAR_H_

#include <AntTweakBar.h>
#include <vector>

class AUiTimeBar 
{
public:
    AUiTimeBar();
    virtual ~AUiTimeBar();
    void initialize();
    void refresh();

public:
    bool paused;
    int currentFrame;
    double currentTime;
    double timeScale;

protected:
    static void TW_CALL onPlayCb(void* usr);
    static void TW_CALL onSetTimeCb(const void *value, void *clientData);
    static void TW_CALL onGetTimeCb(void *value, void *clientData);
    static void TW_CALL onGetFrameCb(void *value, void *clientData);
    static void TW_CALL onSetFrameCb(const void *value, void *clientData);

protected:
    TwBar *mPlayerBar;
    
};

#endif
