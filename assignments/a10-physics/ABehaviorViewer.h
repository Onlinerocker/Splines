#pragma once

#include "AFramework.h"
#include "ASteerable.h"
#include "AWorld.h"
#include "ABehaviors.h" 
#include "AUiTimeBar.h"

class ABehaviorViewer : public AFramework
{
public:
   ABehaviorViewer();
   virtual ~ABehaviorViewer();

   void setup();
   void update();
   void draw();

protected:

   void initializeGui();
   void keyPress(unsigned char key, int specialKey, int x, int y);
   void mousePress(int button, int state, int x, int y);
   void mouseMove(int x, int y);

   enum BehaviorType { 
      SEEK, 
      FLEE, 
      ARRIVAL, 
      DEPARTURE, 
      AVOID, 
      WANDER, 
      ALIGNMENT, 
      SEPARATION, 
      COHESION, 
      FLOCKING, 
      LEADER } 
   _beType;

   virtual void setBehavior(BehaviorType type);
   virtual void reset(int numCharacters, int numObstacles);

   static void TW_CALL onSetBehaviorCb(const void *value, void *clientData);
   static void TW_CALL onGetBehaviorCb(void *value, void *clientData);
   static void TW_CALL onSetNumCharactersCb(const void *value, void *clientData);
   static void TW_CALL onGetNumCharactersCb(void *value, void *clientData);
   static void TW_CALL onSetNumObstaclesCb(const void *value, void *clientData);
   static void TW_CALL onGetNumObstaclesCb(void *value, void *clientData);
   static void TW_CALL onSetParamCb(const void *value, void *clientData);
   static void TW_CALL onGetParamCb(void *value, void *clientData);
   static void TW_CALL onResetCb(void *clientData);

protected:
   AWorld _world;
   AVector3 _target;
   int _numAgents;
   int _numObstacles;

   // Behaviors
   typedef std::map<BehaviorType, ABehavior*> BehaviorMap;
   typedef std::map<BehaviorType, ABehavior*>::iterator BehaviorIt;
   BehaviorMap _behaviors;

   // GUI
   AUiTimeBar _playBar;
   TwBar* _behaviorBar;
   TwType _uiBeType;
   int _modifierState;
   double _lastTime;
   struct UIBeParams 
   {
      ABehaviorViewer* viewer; 
      BehaviorType type; 
      std::string name; 
      std::string options;
      std::string twName;
   };
   std::vector<UIBeParams*> _uiParams;
};
