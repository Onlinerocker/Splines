#ifndef AInterpolator_H_
#define AInterpolator_H_

#include <string>
#include <vector>
#include <map>
#include "AConstants.h"
#include "AVector3.h"

//-------------------------------------------------------------------
// AInterpolator is an abstract base class for 
//   managing control points and performing interpolation
//-------------------------------------------------------------------

class AInterpolator
{
public:
   // destructor
   virtual ~AInterpolator() {}

   // Return an interpolated value for the given segment and time
   // @param segment: ID of the segment to interpolate. First segment has ID = 0
   // @param u: normalized time. u is in the range [0,1]
   virtual AVector3 interpolate(int segment, double time) const = 0;

   // Returns the type of this interpolator
   // Determined by child class; Not settable 
   const std::string& getType() const;

   // Edit a control point based on their raw ID
   // Control points include keys
   // @param ID: Raw ID, Valid IDs range from 0 to getNumControlPoints()-1 
   // @param value: new value for the control point
   void editControlPoint(int ID, const AVector3& value);

   // Return the number of control points across all segments
   int getNumControlPoints() const;

   // Return the value of the control point having raw ID
   // @param ID: Raw ID, Valid IDs range from 0 to getNumControlPoints() 
   const AVector3& getControlPoint(int ID) const;

   // Reset control points
   // Triggers a recomputation of all control points based on the given keys
   // How control points are computed will depend on the concrete child class
   void resetControlPoints(const std::vector<AVector3>& keys);

   // Remove all control points
   void clearControlPoints();

   // The number of control points per segment
   // Determined by child class; Not settable 
   int getNumControlPointsPerSegment() const;

   // Return the control point for the given segment and control point ID
   // @param segment: ID of the segment to interpolate. First segment has ID = 0
   // @param ID: Control point id. Valid range is [0, NumControlPointsPerSegment-1] 
   virtual const AVector3& getControlPoint(int segment, int ID) const;

   // Set the control point at the given segment and control point ID
   // @param segment: ID of the segment to interpolate. First segment has ID = 0
   // @param ID: Control point id. Valid range is [0, NumControlPointsPerSegment-1] 
   // @param value: new value of the control point
   virtual void setControlPoint(int segment, int ID, const AVector3& value);

protected:
   // constructor - callable from child classes only
   AInterpolator(const std::string& type, int numCtrlPtsPerSegment);

   // Computes control points based on the given keys
   // Must be implemented in a child class
   virtual void computeControlPoints(const std::vector<AVector3>& keys) = 0;

   // Compute the raw index of a control point based on the segment and ctrlPtId
   virtual int computeIndex(int segment, int ctrlPtId) const;

   // member variables
   int mNumControlPointsPerSegment;
   std::vector<AVector3> mCtrlPoints;
   std::string mType;
};

//--------------------------------
// Catmull-Rom 
//--------------------------------

class AInterpolatorCatmullRom : public AInterpolator
{
public:
    AInterpolatorCatmullRom() : AInterpolator("Catmull-Rom", 4) {}
    virtual AVector3 interpolate(int segment, double u) const;
    virtual void computeControlPoints(const std::vector<AVector3>& keys);
};

//--------------------------------
// Linear 
//--------------------------------

class AInterpolatorLinear : public AInterpolator
{
public:
    AInterpolatorLinear() : AInterpolator("Linear", 2) {}
    virtual AVector3 interpolate(int segment, double u) const;
    virtual void computeControlPoints(const std::vector<AVector3>& keys);
};

//--------------------------------
// Hermite 
//--------------------------------

class AInterpolatorHermite : public AInterpolator
{
public:
    AInterpolatorHermite() : AInterpolator("Hermite", 4) {}
    virtual AVector3 interpolate(int segment, double u) const;

protected:
    virtual void computeControlPoints(const std::vector<AVector3>& keys);
    virtual int computeIndex(int segment, int ctrlPtId) const;
};

#endif
