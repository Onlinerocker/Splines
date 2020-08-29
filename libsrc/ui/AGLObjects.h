#ifndef AGLObjects_H_
#define AGLObjects_H_

#include "AConstants.h"
#include "AVector3.h"
#include "AMatrix3.h"
#include "ATransform.h"
#include <GL/glut.h>
#include <cmath>

const GLfloat SPECULAR[] = {0.3f, 0.3f, 0.3f, 1.0f};

// global function: ASetColor
//  Set openGL color from AVector3
//  Color is a RGB triplet in range [0,1]
//  
// @param colorVec:: 3x1 vector
// @param alpha: transparency
// 
// @returns: none
inline void ASetColor(const AVector3& colorVec, float alpha = 1.0)
{
    glColor4f(colorVec[0], colorVec[1], colorVec[2], alpha);
}

// global function: ASetMaterial
//  Set openGL material from AVector3
//  Materials support geometry shading when lighting is enabled
//  
// @param colorVec: RGB color in range [0,1]
// 
// @returns: none
inline void ASetMaterial(const AVector3& colorVec)
{
    GLfloat c[4];
    c[0] = colorVec[0];
    c[1] = colorVec[1];
    c[2] = colorVec[2];
    c[3] = 1.0;
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, c);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, c);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, SPECULAR);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 50.0f);
}

// global function: ASetPosition
//  Set openGL translation from AVector3
//  
// @param position: 3x1 position
// 
// @returns: none
inline void ASetPosition(const AVector3& position)
{
    glTranslatef(position[0], position[1], position[2]);
}

// global function: ASetRotation
//  Set openGL rotation matrix from AMatrix3
//  
// @param rotation: 3x3 matrix
// 
// @returns: none
inline void ASetRotation(const AMatrix3& rotation)
{
    GLfloat mat[16];
    rotation.writeToGLMatrix(mat);
    glMultMatrixf(mat);
}

// global function: ASetTransformation
//  Set openGL transformation matrix from ATransform
//  
// @param transform: rotation and translation
// 
// @returns: none
inline void ASetTransform(const ATransform& transform)
{
    GLfloat mat[16];
    transform.writeToGLMatrix(mat);
    glMultMatrixf(mat);
}

// global function: ADrawEllipse
//  Draw a solid ellipse at position given by pos and dimensions size
//  NOTE: Call ASetColor or ASetMaterial before calling this function 
//    to set the color
//  
// @param pos: set the center of the ellipse
// @param size: set the XYZ dimensions of the ellipse
// 
// @returns: none
//
inline void ADrawEllipse(const AVector3& pos, const AVector3& size)
{
    glPushMatrix();
    ASetPosition(pos);
    glScalef(size[0], size[1], size[2]);
    glutSolidSphere(1.0, 12, 12);
    glPopMatrix();
}

inline void ADrawEllipse(const ATransform& xform, const AVector3& size)
{
    glPushMatrix();
    ASetTransform(xform);
    glScalef(size[0], size[1], size[2]);
    glutSolidSphere(1.0, 12, 12);
    glPopMatrix();
}

// global function: ADrawSphere
//  Draw a solid sphere centered at the given position
//  NOTE: Call ASetColor or ASetMaterial before calling this function 
//    to set the color
//  
// @param pos: set the center of the sphere
// @param radius: set the size of the sphere
// 
// @returns: none
//
inline void ADrawSphere(const AVector3& pos, GLfloat radius)
{
    glPushMatrix();
    ASetPosition(pos);
    glutSolidSphere(radius, 12, 12);
    glPopMatrix();
}

inline void ADrawSphere(const ATransform& xform, GLfloat radius)
{
    glPushMatrix();
    ASetTransform(xform);
    glutSolidSphere(radius, 12, 12);
    glPopMatrix();
}

// global function: ADrawCone
//  Draw a solid cone drawn along the Z axis with tip drawn at Z=0
//  NOTE: Call ASetColor or ASetMaterial before calling this function 
//    to set the color
//  
// @param pos: center
// @param rot: rotation around the center
// @param scale: (baseRadius1, baseRadius2, height) dimensions of the cone
// 
// @returns: none
//
inline void ADrawCone(
    const AVector3& pos, 
    const AMatrix3& rot, 
    const AVector3& scale)
{
    glPushMatrix();
    ASetPosition(pos);
    ASetRotation(rot);
    glScalef(scale[0], scale[1], scale[2]);
    glutSolidCone(1.0, 1.0, 12, 12);
    glPopMatrix();
}

inline void ADrawCone(const ATransform& xform, const AVector3& scale)
{
    glPushMatrix();
    ASetTransform(xform);
    glScalef(scale[0], scale[1], scale[2]);
    glutSolidCone(1.0, 1.0, 12, 12);
    glPopMatrix();
}


// global function: ADrawCube
//  Draw a solid cube centered at position and with given rotation and size
//  NOTE: Call ASetColor or ASetMaterial before calling this function 
//    to set the color
//  
// @param pos: center position
// @param rot: rotation around center
// @param scale: XYZ dimensions
// 
// @returns: none
//
inline void ADrawCube(
    const AVector3& position, 
    const AMatrix3& rotation, 
    const AVector3& scale) 
{
    glPushMatrix();
    ASetPosition(position);
    ASetRotation(rotation);
    glScalef(scale[0], scale[1], scale[2]);
    glutSolidCube(1.0);
    glPopMatrix();
}

inline void ADrawCube(const ATransform& xform, const AVector3& scale) 
{
    glPushMatrix();
    ASetTransform(xform);
    glScalef(scale[0], scale[1], scale[2]);
    glutSolidCube(1.0);
    glPopMatrix();
}


// global function: ADrawLine
//  Draw a line from start to end
//  NOTE: Call ASetColor before calling this function 
//    to set the color
//  
// @param start: position
// @param end: position
// 
// @returns: none
//
inline void ADrawLine(const AVector3& start, const AVector3& end)
{
	glPushAttrib(GL_LIGHTING);	glDisable(GL_LIGHTING);	glBegin(GL_LINES);	glVertex3f(start[0], start[1], start[2]);	glVertex3f(end[0], end[1], end[2]);	glEnd();	glPopAttrib();
}

// global function: ADrawTeapot
//  Draw a solid teapot centered at the given position
//  NOTE: Call ASetColor or ASetMaterial before calling this function 
//    to set the color
//  
// @param pos: the position
// @param rot: rotate the teapot around its center
// @param scale: change the size of the teapot
// 
// @returns: none
//
inline void ADrawTeapot(
    const AVector3& pos, 
    const AMatrix3& rot, 
    const AVector3& scale )
{
    glPushMatrix();
    ASetPosition(pos);
    ASetRotation(rot);
    glScalef(scale[0], scale[1], scale[2]);
    glutSolidTeapot(1.0);
    glPopMatrix();
}

inline void ADrawTeapot( const ATransform& xform, const AVector3& scale )
{
    glPushMatrix();
    ASetTransform(xform);
    glScalef(scale[0], scale[1], scale[2]);
    glutSolidTeapot(1.0);
    glPopMatrix();
}

inline void AUnitCylinder()
{
    static GLUquadricObj *quadratic = gluNewQuadric();
    gluCylinder(quadratic, 1.0, 1.0, 1.0, 12, 12);
    glPushMatrix();
        glTranslatef(0,0,1);
        gluDisk(quadratic, 0, 1, 12, 1);
    glPopMatrix();
    glPushMatrix();
        glRotatef(180, 0,1,0);
        gluDisk(quadratic, 0, 1, 12, 1);
    glPopMatrix();
}


inline void ADrawCylinder( const ATransform& xform, const AVector3& scale )
{
    glPushMatrix();
    ASetTransform(xform);
    glScalef(scale[0], scale[1], scale[2]);
    AUnitCylinder();
    glPopMatrix();
}

// global function: ADrawTorus
//  Draw a solid torus (e.g. doughnut) oriented along the Z axis 
//    and centered at the given position
//  The inner and out radius determine the thickness of the 'doughnut'
//  NOTE: Call ASetColor or ASetMaterial before calling this function 
//    to set the color
//  
// @param pos: offset the default position of the tip
// @param rot: rotate the cone from the default alignment along the Z axis
// @param scale: change the size of the cone
// @param innerRadius: distance from center
// @param outerRadius: distance from center
// 
// @returns: none
//
inline void ADrawTorus(
    const AVector3& pos, 
    const AMatrix3& rot, 
    const AVector3& scale, 
    GLfloat innerRadius, GLfloat outerRadius)
{
    glPushMatrix();
    ASetPosition(pos);
    ASetRotation(rot);
    glScalef(scale[0], scale[1], scale[2]);
    glutSolidTorus(innerRadius, outerRadius, 12, 12);
    glPopMatrix();
}

inline void ADrawTorus( const ATransform& xform, const AVector3& scale, 
    GLfloat innerRadius, GLfloat outerRadius)
{
    glPushMatrix();
    ASetTransform(xform);
    glScalef(scale[0], scale[1], scale[2]);
    glutSolidTorus(innerRadius, outerRadius, 12, 12);
    glPopMatrix();
}

// global function: ADrawLimb
//  Draw a solid ellipsoid oriented along the direction given by 
//    start/end position
//  NOTE: Call ASetColor or ASetMaterial before calling this function 
//    to set the color
//  
// @param startPosition: the starting tip of the ellipsoid
// @param endPosition: the ending tip of the ellipsoid
// @param scale: the half width of the ellipsoid (thickness of limb)
// 
// @returns: none
//
inline void ADrawLimb(
    const AVector3& startPosition, 
    const AVector3& endPosition, 
    float radius)
{
    AVector3 direction = endPosition - startPosition; 
    float length = direction.length();
    direction /= length;
    float x = direction[0] * direction[0];
    float y = direction[1] * direction[1];
    float z = direction[2] * direction[2];
    float dx = y + z;
    float dy = x + z;
    float dz = x + y;
    unsigned int eAxis;
    AVector3 axis;
    float angle;
    if (dx >= dy && dx >= dz)
    {
        eAxis = 0;
        axis = AVector3::Cross(AVector3::AxisX, direction);
        angle = acos(AVector3::Dot(direction, AVector3::AxisX)) * ARad2Deg;
    }
    else if (dy >= dx && dy >= dz)
    {
        eAxis = 1;
        axis = AVector3::Cross(AVector3::AxisY, direction);
        angle = acos(AVector3::Dot(direction, AVector3::AxisY)) * ARad2Deg;
    }
    else
    {
        eAxis = 2;
        axis = AVector3::Cross(AVector3::AxisZ, direction);
        angle = acos(AVector3::Dot(direction, AVector3::AxisZ)) * ARad2Deg;
    }
    AVector3 center = (endPosition + startPosition) / 2.0f;
    AVector3 scale;
    switch(eAxis)
    {
    case 0: scale = AVector3(length / 2.0f, radius, radius); break;
    case 1: scale = AVector3(radius, length / 2.0f, radius); break;
    case 2: scale = AVector3(radius, radius, length / 2.0f); break;
    }

    glPushMatrix();
    glTranslatef(center[0], center[1], center[2]);
    glRotatef(angle, axis[0], axis[1], axis[2]);
    glScalef(scale[0], scale[1], scale[2]);
    glutSolidSphere (1.0, 24, 12);
    glPopMatrix();
}


#endif
