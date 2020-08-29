#include "AWorld.h"
#include "AGLObjects.h"
#include <functional>
#include <random>

static std::default_random_engine generator;
static std::uniform_real_distribution<double> distribution(0,1);
static auto dice = std::bind(distribution, generator);

bool AWorld::kDrawObstacles = true;

AWorld::AWorld() : 
   _dimension(AVector3(1000,0,1000)), _empty{0,AVector3(0,0,0)}, _agents(), _obstacles()
{
}

AWorld::AWorld(const AVector3& dim) : 
   _dimension(dim), _empty{0,AVector3(0,0,0)}, _agents(), _obstacles()
{
}

AWorld::~AWorld() 
{
   clear();
}

void AWorld::clear()
{
   for (unsigned int i = 0; i < _agents.size(); i++)
   {
      delete _agents[i];
   }
   _agents.clear();
   _obstacles.clear();
}

void AWorld::reset()
{
   for (unsigned int i = 0; i < _agents.size(); i++)
   {
      _agents[i]->reset();
   }
}

void AWorld::setNumAgents(int numAgents)
{
   for (int i = 0; i < numAgents; i++)
   {
      AVector3 pos = AVector3(dice(), dice(), dice());
      pos[0] = (pos[0] - 0.5) * _dimension[0];
      pos[1] = (pos[1] - 0.5) * _dimension[1];
      pos[2] = (pos[2] - 0.5) * _dimension[2];
      std::cout << pos << std::endl;
      createAgent(pos);
   }
}

ASteerable& AWorld::getAgent(int i)
{
   return *(_agents[i]);
}

const ASteerable& AWorld::getAgent(int i) const
{
   return *(_agents[i]);
}

void AWorld::createAgent(const AVector3& pos)
{
   // ASN FIX: Motion crashes (needs copy/assn operators) unless 
   // we create pts objects
   ASteerable* agent = new ASteerable();
   agent->reset(pos);
   _agents.push_back(agent);
}

int AWorld::getNumAgents() const
{
   return _agents.size();
}

void AWorld::setNumObstacles(int num)
{
   for (int i = 0; i < num; i++)
   {
      AVector3 pos(dice(), dice(), dice());
      pos[0] = (pos[0] - 0.5) * _dimension[0];
      pos[1] = (pos[1] - 0.5) * _dimension[1];
      pos[2] = (pos[2] - 0.5) * _dimension[2];
      double r = dice() * 300;
      createObstacle(pos, r);
   } 
}

void AWorld::createObstacle(const AVector3& pos, double r)
{
   AObstacle obs{r,pos};
   _obstacles.push_back(obs);
}

AObstacle& AWorld::getObstacle(int i)
{
   return _obstacles[i];
}

const AObstacle& AWorld::getObstacle(int i) const
{
   return _obstacles[i];
}

int AWorld::getNumObstacles() const
{
   return _obstacles.size();
}

void AWorld::draw()
{
   for (unsigned int i = 0; i < _agents.size(); i++)
   {
      _agents[i]->draw();
   }

   if (kDrawObstacles)
   {
      ASetMaterial(AVector3(0.8,0.8,0.8));
      for (unsigned int i = 0; i < _obstacles.size(); i++)
      {
         ADrawEllipse(_obstacles[i].position, _obstacles[i].radius * AVector3(1,1,1));
      }
   }
}

