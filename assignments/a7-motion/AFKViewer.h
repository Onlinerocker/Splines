#pragma once

#include <string>
#include "AFramework.h"
#include "AUiDirBar.h"
#include "AUiTimeBar.h"
#include "ASkeletonDrawer.h"
#include "AnimationToolkit.h"

class AFKViewer : public AFramework
{
public:
    AFKViewer();
    virtual ~AFKViewer();
    virtual void loadDir(const std::string& dir);
    virtual void loadMotion(const std::string& filename);
    virtual void draw();
    virtual void update();

protected:
    void initializeGui();
    static void onFileCb(const char* filename, void* usr);

protected:
    ASkeletonDrawer _drawer;
    ASkeleton _skeleton;
    AMotion _motion;
    AUiDirBar _dirBar;
    AUiTimeBar _playBar;
};
