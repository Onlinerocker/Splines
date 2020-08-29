#include <string>
#include "AFKViewer.h"
#include "ABVHReader.h"
#include "AOsUtils.h"
#include "GL/glew.h"
#include "GL/glut.h"
#include <algorithm>
#include <AntTweakBar.h>

AFKViewer::AFKViewer() : AFramework(AFramework::Perspective)
{
    _dirBar.setFileClickedCb(onFileCb, this);
}

AFKViewer::~AFKViewer()
{
}

void AFKViewer::initializeGui()
{
    _dirBar.initialize();
    _playBar.initialize();
}

void AFKViewer::loadDir(const std::string& dir)
{
    _dirBar.loadDir(dir);
}

void AFKViewer::loadMotion(const std::string& filename)
{
    ABVHReader reader;
    reader.load(filename, _skeleton, _motion);
    _dirBar.setFilename(filename);
}

void AFKViewer::update()
{
    // handle UI
    bool paused = _playBar.paused;
    if (!paused)
    {
        _playBar.currentTime = _playBar.currentTime + dt() * _playBar.timeScale;
        _playBar.currentFrame = _motion.getKeyID(_playBar.currentTime);
    }
    else
    {
        _playBar.currentFrame = _playBar.currentFrame % _motion.getNumKeys();
        _playBar.currentTime = _playBar.currentFrame * _motion.getDeltaTime();
    }
    _motion.update(_skeleton, _playBar.currentTime);
    _playBar.refresh();
}

void AFKViewer::draw()
{
    _drawer.draw(_skeleton);
}

void AFKViewer::onFileCb(const char* filename, void* usr)
{
    ((AFKViewer*) usr)->loadMotion(filename);
}

int main(int argc, char** argv)
{
   AFKViewer viewer;
   viewer.init(argc, argv);
   viewer.loadMotion("../motions/Beta/walking.bvh");
   viewer.loadDir("../motions/Beta/");
   viewer.run();
}
