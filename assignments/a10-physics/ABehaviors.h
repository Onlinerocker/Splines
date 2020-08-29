#ifndef _BEHAVIOR_H
#define _BEHAVIOR_H

#include <string>
#include "AVector3.h"
#include "ASteerable.h"
#include "AObstacle.h"
#include "AWorld.h"

class ABehavior
{
public:
   virtual ~ABehavior() {}

   virtual AVector3 calculateDesiredVelocity(
      const ASteerable& actor, const AWorld& world, const AVector3& target) = 0;

   const std::string& getName() const;

   int getNumParams() const;
   const std::string& getParamName(int i) const;
   double getParamValue(int i) const; 
   double getParam(const std::string& name) const;
   void setParam(const std::string& name, double v);

protected:
   ABehavior(const char* name);
   std::string _name;
   std::map<std::string, double> _params;
};

class ASeek : public ABehavior
{
public:
   ASeek();
   virtual AVector3 calculateDesiredVelocity(
      const ASteerable& actor, const AWorld& world, const AVector3& target);
};

class AFlee : public ABehavior
{
public:
   AFlee();
   virtual AVector3 calculateDesiredVelocity(
      const ASteerable& actor, const AWorld& world, const AVector3& target);
};

class AArrival : public ABehavior
{
public:
   AArrival();
   virtual AVector3 calculateDesiredVelocity(
      const ASteerable& actor, const AWorld& world, const AVector3& target);
};

class ADeparture : public ABehavior
{
public:
   ADeparture();
   virtual AVector3 calculateDesiredVelocity(
      const ASteerable& actor, const AWorld& world, const AVector3& target);
};

class AAvoid : public ABehavior
{
public:
   AAvoid();
   virtual AVector3 calculateDesiredVelocity(
      const ASteerable& actor, const AWorld& world, const AVector3& target);
};

class AWander : public ABehavior
{
public:
   AWander();
   virtual AVector3 calculateDesiredVelocity(
      const ASteerable& actor, const AWorld& world, const AVector3& target);
};

class ASeparation : public ABehavior
{
public:
   ASeparation();
   virtual AVector3 calculateDesiredVelocity(
      const ASteerable& actor, const AWorld& world, const AVector3& target);
};

class ACohesion : public ABehavior
{
public:
   ACohesion();
   virtual AVector3 calculateDesiredVelocity(
      const ASteerable& actor, const AWorld& world, const AVector3& target);
};

class AAlignment : public ABehavior
{
public:
   AAlignment();
   virtual AVector3 calculateDesiredVelocity(
      const ASteerable& actor, const AWorld& world, const AVector3& target);
};

class AFlocking : public ABehavior
{
public:
   AFlocking();
   virtual AVector3 calculateDesiredVelocity(
      const ASteerable& actor, const AWorld& world, const AVector3& target);
};

class ALeader : public ABehavior
{
public:
   ALeader();
   virtual AVector3 calculateDesiredVelocity(
      const ASteerable& actor, const AWorld& world, const AVector3& target);
};

//----------------------------------------------------
// ABehavior implementation

inline const std::string& ABehavior::getName() const 
{ 
   return _name; 
}

inline int ABehavior::getNumParams() const 
{ 
   return _params.size(); 
}

inline const std::string& ABehavior::getParamName(int i) const 
{ 
   std::map<std::string, double>::const_iterator it = _params.begin();
   std::advance(it,i);
   return it->first; 
}

inline double ABehavior::getParamValue(int i) const 
{ 
   std::map<std::string, double>::const_iterator it = _params.begin();
   std::advance(it,i);
   return it->second; 
}

inline double ABehavior::getParam(const std::string& name) const
{ 
   std::map<std::string, double>::const_iterator it = _params.find(name);
   return it != _params.end()? it->second : 0;
}

inline void ABehavior::setParam(const std::string& name, double v) 
{ 
   _params[name] = v; 
}


#endif
