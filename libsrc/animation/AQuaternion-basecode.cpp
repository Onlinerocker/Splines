#include "AQuaternion.h"
#include "AMatrix3.h"
#include "AVector3.h"
#include <math.h>

AQuaternion AQuaternion::Slerp(const AQuaternion& q0, const AQuaternion& q1, double t)
{
	// TODO
	if(q0 == q1)
		return q0;

	double dot = Dot(q0, q1);
	double theta = acos(dot);
	AQuaternion newQ1 = q1;

	if(dot < 0 || theta > 90)
	{
		newQ1 = -q1;
		dot = Dot(q0, newQ1);
		theta = acos(dot);
	}

	AQuaternion term = (sin(theta - theta*t) / sin(theta)) * q0;
	AQuaternion term1 = (sin(theta * t) / sin(theta)) * newQ1;

	return term + term1;
}

void AQuaternion::toAxisAngle (AVector3& axis, double& angleRad) const
{
	axis = AVector3(0,0,0);
	angleRad = 2 * acos(mW);

	//axis[0] = mX / (sin(angleRad / 2.0));

	if(sqrt(1-mW * mW) == 0)
		std::cout << "test" << std::endl;

	axis[0] = mX / sqrt(1-mW * mW);
	axis[1] = mY / sqrt(1-mW * mW);
	axis[2] = mZ / sqrt(1-mW * mW);
}

void AQuaternion::fromAxisAngle (const AVector3& axis, double angleRad)
{
	// TODO
	AVector3 xyz = axis * sin(angleRad / 2.0);

	mX = xyz[0];
	mY = xyz[1];
	mZ = xyz[2];
	mW = cos(angleRad / 2.0);
	normalize();
}

AMatrix3 AQuaternion::toMatrix () const
{
	AMatrix3 mat = AMatrix3();

	mat[0][0] = 1 - 2*(pow(mY, 2) + pow(mZ, 2));
	mat[0][1] = 2 * (mX*mY - mW*mZ);
	mat[0][2] = 2 * (mX*mZ + mW*mY);

	mat[1][0] = 2 * (mX*mY + mW*mZ);
	mat[1][1] = 1 - 2*(pow(mX, 2) + pow(mZ, 2));
	mat[1][2] = 2 * (mY*mZ - mW*mX);

	mat[2][0] = 2 * (mX*mZ - mW*mY);
	mat[2][1] = 2 * (mY*mZ + mW*mX);
	mat[2][2] = 1 - 2*(pow(mY, 2) + pow(mX, 2));

	return mat;
}

void AQuaternion::fromMatrix(const AMatrix3& rot)
{
	float *vals = new float[4]; //0=x, 1=y, 2=z, 3=w
	vals[0] = (1 + rot[0][0] - rot[1][1] - rot[2][2]) / 4.0; //x^2
	vals[1] = (1 - rot[0][0] + rot[1][1] - rot[2][2]) / 4.0; //y^2
	vals[2] = (1 - rot[0][0] - rot[1][1] + rot[2][2]) / 4.0; //z^2
	vals[3] = (1 + rot[0][0] + rot[1][1] + rot[2][2]) / 4.0; //w^2

	int max = 0;

	for(int x=1; x<4; x++){
		if(vals[x] > vals[max]){
			max = x;
		}
	}

	if(max == 0){
		mX = sqrt(vals[max]);
		mW = ((rot[1][2] - rot[2][1]) / -4.0) / mX;
		mY = ((rot[0][1] + rot[1][0]) / 4.0) / mX;
		mZ = ((rot[0][2] + rot[2][0]) / 4.0) / mX;
	}else if(max == 1){
		mY = sqrt(vals[max]);
		mW = ((rot[0][2] - rot[2][0]) / 4.0) / mY;
		mX = ((rot[0][1] + rot[1][0]) / 4.0) / mY;
		mZ = ((rot[1][2] + rot[2][1]) / 4.0) / mY;
	}else if(max == 2){
		mZ = sqrt(vals[max]);
		mW = ((rot[0][1] - rot[1][0]) / -4.0) / mZ;
		mX = ((rot[0][2] + rot[2][0]) / 4.0) / mZ;
		mY = ((rot[1][2] + rot[2][1]) / 4.0) / mZ;
	}else if(max == 3){
		mW = sqrt(vals[max]);
		mX = ((rot[1][2] - rot[2][1]) / -4.0) / mW;
		mY = ((rot[0][2] - rot[2][0]) / 4.0) / mW;
		mZ = ((rot[0][1] - rot[1][0]) / -4.0) / mW;
	}
}

