#include "ABehaviorViewer.h"
#include <string>
#include "ACamera.h"
#include "AGLObjects.h"
#include "GL/glew.h"
#include "GL/glut.h"
#include <algorithm>
#include <AntTweakBar.h>

ABehaviorViewer::ABehaviorViewer() : 
   AFramework(AFramework::Perspective),
   _world(), _target(100,0,100),
   _numAgents(5), _numObstacles(5)
{
   _behaviors[SEEK] = new ASeek();
   _behaviors[FLEE] = new AFlee();
   _behaviors[ARRIVAL] = new AArrival();
   _behaviors[DEPARTURE] = new ADeparture();
   _behaviors[COHESION] = new ACohesion();
   _behaviors[ALIGNMENT] = new AAlignment();
   _behaviors[SEPARATION] = new ASeparation();
   _behaviors[LEADER] = new ALeader();
   _behaviors[FLOCKING] = new AFlocking();
   _behaviors[AVOID] = new AAvoid();
   _behaviors[WANDER] = new AWander();
}

ABehaviorViewer::~ABehaviorViewer()
{
   for (BehaviorIt it = _behaviors.begin(); it != _behaviors.end(); it++)
   {
      delete it->second;
   }
   _behaviors.clear();

   for (unsigned int i = 0; i < _uiParams.size(); i++)
   {
      delete _uiParams[i];
   }
   _uiParams.clear();
}

void ABehaviorViewer::setup()
{

   _beType = SEEK;
   reset(_numAgents, _numObstacles);
}

void ABehaviorViewer::setBehavior(BehaviorType type)
{
    _beType = type;
    AWorld::kDrawObstacles = (_beType == AVOID);
}

void ABehaviorViewer::draw()
{
   _world.draw();

   ASetMaterial(AVector3(1,0,0));
   ADrawEllipse(_target, AVector3(5,5,5));
}

void ABehaviorViewer::update()
{
   double t = dt();
   bool paused = _playBar.paused;
   if (!paused)
   {
      t = t * _playBar.timeScale;
      _playBar.currentTime = _playBar.currentTime + t;
      _playBar.currentFrame = 0;
   }
   else
   {
      t = _playBar.currentTime - _lastTime;
      _playBar.currentFrame = 0;
   }
   
   _playBar.refresh();
   _lastTime = _playBar.currentTime;

   for (int i = 0; i < _world.getNumAgents(); i++)
   {
      ASteerable& agent = _world.getAgent(i);
      AVector3 dvel = _behaviors[_beType]->calculateDesiredVelocity(agent, _world, _target);
      agent.update(dvel, t);
   }
}

void ABehaviorViewer::mousePress(int button, int state, int x, int y)
{
   _modifierState = state;
   mouseMove(x, y);
}

void ABehaviorViewer::mouseMove(int x, int y)
{
   if (_modifierState == GLUT_ACTIVE_CTRL) // move target
   {
      GLint viewport[4];
      glGetIntegerv(GL_VIEWPORT, viewport);
      if (viewport[3] == 0){
            viewport[3] = 1;
      }
      AVector3 target(0, 0, 0);
      getCamera()->screenToWorld(x, viewport[3] - y, target);

      AVector3 origin = getCamera()->getPosition();
      AVector3 dir = target - origin;

      // Intersect with XZ plane when?
      float t = -origin[1] / dir[1];
      _target = origin + t*dir;
   }
}

void ABehaviorViewer::keyPress(unsigned char key, int special, int x, int y)
{
   if (key == ' ') reset(_numAgents, _numObstacles);
}

void ABehaviorViewer::reset(int numAgents, int numObstacles)
{
   getCamera()->frameVolume(AVector3(0,0,0), AVector3(1000,1500,1000));
   ACamera::gDfltLook = AVector3(0,0,0);
   ACamera::gDfltEye = AVector3(900,800,900);
   getCamera()->reset();

   _numAgents = numAgents;
   _numObstacles = numObstacles;
   _world.clear();
   _world.setNumAgents(_numAgents);
   _world.setNumObstacles(_numObstacles);
   _world.reset();

   setBehavior(_beType);
}

void ABehaviorViewer::initializeGui()
{
   _playBar.initialize();

   TwDefine(" 'Time controls' size='200 100' position='5 5' "
      "iconified=false fontresizable=false alpha=200");

   _behaviorBar = TwNewBar("Behavior controls");
   TwDefine(" 'Behavior controls' size='200 450' position='5 110' "
      "iconified=false fontresizable=false alpha=200");

   TwAddButton(_behaviorBar, "Reset", onResetCb, this, "");
   TwAddVarCB(_behaviorBar, "Num characters", TW_TYPE_INT32, 
      onSetNumCharactersCb, onGetNumCharactersCb, this, "");
   TwAddVarCB(_behaviorBar, "Num obstacles", TW_TYPE_INT32, 
      onSetNumObstaclesCb, onGetNumObstaclesCb, this, "");
   TwAddSeparator(_behaviorBar, "Sep", "");

   TwEnumVal beTypeEV[] = { 
        { SEEK, "Seek" }, 
        { FLEE, "Flee" }, 
        { ARRIVAL, "Arrival" },
        { DEPARTURE, "Departure" },
        { AVOID, "Avoid" },
        { ALIGNMENT, "Alignment" },
        { WANDER, "Wander" },
        { SEPARATION, "Separation" },
        { COHESION, "Cohesion" },
        { FLOCKING, "Flocking" },
        { LEADER, "Leader" }
   };
   _uiBeType = TwDefineEnum("BehaviorType", beTypeEV, 11);
   TwAddVarCB(_behaviorBar, "Behavior", _uiBeType, 
      onSetBehaviorCb, onGetBehaviorCb, this, " ");


   for (BehaviorIt it = _behaviors.begin(); it != _behaviors.end(); ++it)
   {
      std::string groupName = it->second->getName();
      for (int i = 0; i < it->second->getNumParams(); i++)
      {
         std::string paramName = it->second->getParamName(i);
         std::string options = " group=\"" + groupName + "\" label=\"" + paramName + "\""; 
         std::string twName = groupName+paramName;
         std::cout << "adding: " << groupName << " " << paramName << " " << options << std::endl;
         UIBeParams* params = new UIBeParams;
         params->viewer = this;
         params->type = it->first;
         params->name = it->second->getParamName(i);
         params->options = options;
         params->twName = twName;
         _uiParams.push_back(params);

         TwAddVarCB(_behaviorBar, params->twName.c_str(), TW_TYPE_DOUBLE, 
            onSetParamCb, onGetParamCb, params, params->options.c_str());
      }
   }
}

void TW_CALL ABehaviorViewer::onSetBehaviorCb(const void *value, void *clientData)
{
    ABehaviorViewer* viewer = ((ABehaviorViewer*)clientData);
    BehaviorType v = *(const BehaviorType *)value;  // for instance
    viewer->setBehavior(v);
}

void TW_CALL ABehaviorViewer::onGetBehaviorCb(void *value, void *clientData)
{
    ABehaviorViewer* viewer = ((ABehaviorViewer*)clientData);
    *static_cast<BehaviorType *>(value) = viewer->_beType;
}

void TW_CALL ABehaviorViewer::onSetNumObstaclesCb(const void *value, void *clientData)
{
    ABehaviorViewer* viewer = ((ABehaviorViewer*)clientData);
    int v = *(const int *)value;  // for instance
    viewer->reset(viewer->_numAgents, v);
}

void TW_CALL ABehaviorViewer::onGetNumObstaclesCb(void *value, void *clientData)
{
    ABehaviorViewer* viewer = ((ABehaviorViewer*)clientData);
    *static_cast<int *>(value) = viewer->_numObstacles;
}

void TW_CALL ABehaviorViewer::onSetNumCharactersCb(const void *value, void *clientData)
{
    ABehaviorViewer* viewer = ((ABehaviorViewer*)clientData);
    int v = *(const int *)value;  // for instance
    viewer->reset(v, viewer->_numObstacles);
}

void TW_CALL ABehaviorViewer::onGetNumCharactersCb(void *value, void *clientData)
{
    ABehaviorViewer* viewer = ((ABehaviorViewer*)clientData);
    *static_cast<int *>(value) = viewer->_numAgents;
}

void TW_CALL ABehaviorViewer::onSetParamCb(const void *value, void *clientData)
{
   UIBeParams* params = ((UIBeParams*)clientData);
   ABehaviorViewer* viewer = params->viewer;
   double v = *(const double *)value;  
   viewer->_behaviors[params->type]->setParam(params->name, v);
}

void TW_CALL ABehaviorViewer::onGetParamCb(void *value, void *clientData)
{
   UIBeParams* params = ((UIBeParams*)clientData);
   ABehaviorViewer* viewer = params->viewer;
   *static_cast<double *>(value) = viewer->_behaviors[params->type]->getParam(params->name);
}

void TW_CALL ABehaviorViewer::onResetCb(void *clientData)
{
    ABehaviorViewer* viewer = ((ABehaviorViewer*)clientData);
    viewer->reset(viewer->_numAgents, viewer->_numObstacles);
}

int main(int argc, char** argv)
{
   ABehaviorViewer viewer;
   viewer.init(argc, argv);
   viewer.run();
}
