//------------------------------------------------------------------------
// Copyright (C) 2009 Aline Normoyle


#ifndef camera_H_
#define camera_H_

#include "GL/gl.h"
#include "AVector3.h"

class ACamera
{
public:
   ACamera();
   virtual ~ACamera();

   // Draw projection and eyepoint
   virtual void draw();

   // Print eyepoint position and basis
   virtual void print();

   // Initialize the camera with glyLookAt parameters
   virtual void set(const AVector3& eyepos, const AVector3& look, const AVector3& up);

   // Set camera parameters to fit the given view volume
   virtual void frameVolume(const AVector3& pos, const AVector3& dim);

   // Get camera state
   virtual void setPosition(const AVector3& pos);
   virtual const AVector3& getPosition() const;
   virtual const AVector3& getUp() const;
   virtual const AVector3& getBackward() const;
   virtual const AVector3& getRight() const;
   virtual AVector3 getRelativePosition(float left, float up, float forward);
   virtual float heading() const;
   virtual float pitch() const;

   // Camera frustrum managements
   virtual void setProjection(float vfov, float aspect, float zNear, float zFar);
   virtual void getProjection(float& vfov, float& aspect, float& zNear, float& zFar);
   virtual void getViewport(int& x, int& y, int& w, int& h);

   // Relative movement commands
   virtual void moveLeft(float scale = 1.0);
   virtual void moveRight(float scale = 1.0);
   virtual void moveUp(float scale = 1.0);
   virtual void moveDown(float scale = 1.0);
   virtual void moveForward(float scale = 1.0);
   virtual void moveBack(float scale = 1.0);

   virtual void turnLeft(float scale = 1.0);
   virtual void turnRight(float scale = 1.0);
   virtual void turnUp(float scale = 1.0);
   virtual void turnDown(float scale = 1.0);

   virtual void orbitLeft(float scale = 1.0);
   virtual void orbitRight(float scale = 1.0);
   virtual void orbitUp(float scale = 1.0);
   virtual void orbitDown(float scale = 1.0);

   // Reset to original state
   virtual void reset();

   // Conversion utilities between screen and world coordinates
   virtual bool screenToWorld(int screenX, int screenY, AVector3& worldCoords);
   virtual bool worldToScreen(const AVector3& worldCoords, int& screenX, int& screenY);

protected:
   enum Dir { NONE, F, B, L, R, U, D, TL, TR, TU, TD} mDir, mTurnDir;
   virtual void turn(AVector3& v, AVector3& n, float amount);
   virtual void move(float dU, float dV, float dN);
   virtual void orbit(float h, float p);

protected:
   float mSpeed, mTurnRate;

   AVector3 mEye; // camera position
   float mHeading, mPitch, mRadius;
   float mVfov, mAspect, mNear, mFar; // projection parameters
   
   // Basis of camera local coord system
   AVector3 mU; // up
   AVector3 mV; // v points right
   AVector3 mN; // -n points forward

   // Cache useful values
   GLdouble mProjMatrix[16];
   GLdouble mModelMatrix[16];
   GLint mViewport[4];

public:

   // Defaults
   static AVector3 gDfltEye;
   static AVector3 gDfltUp;
   static AVector3 gDfltLook;
   static float gDfltVfov;
   static float gDfltAspect;
   static float gDfltNear;
   static float gDfltFar;
   static float gDfltSpeed;
   static float gDfltTurnRate;
};

#endif
