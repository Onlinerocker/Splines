#pragma once

#include "AnimationToolkit.h"
#include "ASteerable.h"
#include "AObstacle.h"

// container for objects representing the state of the 'world'
class AWorld
{
public:
   AWorld();
   AWorld(const AVector3& dim);
   virtual ~AWorld();

   // drawing
   void draw();

   // empty the world
   void clear();

   // create a new random world with same #agents and #obstacles
   void reset();

   // create agents with random position
   void setNumAgents(int numAgents);
   // create agent with given position
   void createAgent(const AVector3& pos);
   // return ith agent, i must be between 0 and getNumAgents
   const ASteerable& getAgent(int i) const;
   ASteerable& getAgent(int i);
   // return num agents
   int getNumAgents() const;

   // create num obstacles with random size and pos
   void setNumObstacles(int num);
   // create an obstacle with the given pos and r
   void createObstacle(const AVector3& pos, double r);
   // get ith obstacles, i should be between 0 and getNumObstacles
   const AObstacle& getObstacle(int i) const;
   AObstacle& getObstacle(int i);
   // return num obstacles
   int getNumObstacles() const;

private:
   AVector3 _dimension;
   AObstacle _empty;
   std::vector<ASteerable*> _agents;
   std::vector<AObstacle> _obstacles;

public:
   static bool kDrawObstacles;
};

