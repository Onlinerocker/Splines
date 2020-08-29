#ifndef ASpline_H_
#define ASpline_H_

#include "AInterpolator.h"

#include <map>
#include <vector>

class ASpline
{
public:
   // constructor
   ASpline();

   // destructor
   virtual ~ASpline();

   // Set the interpolation type used for computing control 
   //     points and interpolation
   // @param type: must correspond to a valid AInterpolator name
   void setInterpolationType(const std::string& type);

   // Returns the current interpolation type
   const std::string&  getInterpolationType() const;

   // Returns the value at realtime t
   // @param t: a non-negative value
   AVector3 getValue(double t, bool loop = true) const;

   // Edit the key with the given ID
   // Triggers a recomputation of control points
   // @param keyID: Valid IDs are in range [0, getNumKeys()-1]
   void editKey(int keyID, const AVector3& value); 

   // Appends a key with the given time and value
   // Triggers a recomputation of control points
   // Time must be larger than all previously added keys
   // (e.g,user must ensure keys are sorted)
   // @param time: a non-negative value
   // @param value: the key's value
   int appendKey(double time, const AVector3& value);

   // Delete the key with the given ID
   // Triggers a recomputation of control points
   // @param keyID: Valid IDs are in range [0, getNumKeys()-1]
   void deleteKey(int keyID);

   // Return the value of the key with the given ID
   // @param keyID: Valid IDs are in range [0, getNumKeys()-1]
   AVector3 getKey(int keyID) const;

   // Return the time  of the key with the given ID
   // @param keyID: Valid IDs are in range [0, getNumKeys()-1]
   double getTime(int keyID) const;

   // Return the number of keys
   int getNumKeys() const;

   // Returns the number of segments (numkeys-1 if numkeys > 1)
   int getNumSegments() const;

   // Removes all keys
   // Triggers a recomputation of control points
   void clear();

   // Returns the duration of the spline
   double getDuration() const;

   // Returns the percentage complete based on time t
   // For example if the duration is 4 and t = 2, we return 0.5
   // @param time: a non-negative value
   double getNormalizedDuration(double t) const; 

   // Returns the key ID corresponding to time
   int getKeyID(double time) const;

   // Returns the number of control points (See AInterpolator.h)
   int getNumControlPoints() const;

   // Returns the value of control point by raw ID (See AInterpolator.h)
   const AVector3& getControlPoint(int id) const;

   // Returns the value of control point by segment and control point ID (See AInterpolator.h)
   const AVector3& getControlPoint(int segment, int id) const;

   // Returns the number of control points (See AInterpolator.h)
   void editControlPoint(int id, const AVector3& v);

protected:
   // Computes the segment containing t
   int computeSegment(double t) const;

protected:
   mutable bool mDirty;
   AInterpolator* mInterpolator;

   std::vector<AVector3> mKeys;
   std::vector<double> mTimes;
};
#endif
