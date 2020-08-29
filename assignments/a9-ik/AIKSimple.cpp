#include <string>
#include <cmath>
#include "AIKSimple.h"
#include "ACamera.h"
#include "GL/glew.h"
#include "GL/glut.h"
#include <algorithm>
#include <AntTweakBar.h>
#include <iostream>
#include "ASkeleton.h"

AIKSimple::AIKSimple() : 
   AFramework(AFramework::Perspective),
   mDrawer(),
   mGoalPosition()
{
}

void AIKSimple::setupCharacter()
{
    AVector3 pd(-4, 3, 0);
    ATransform root;
    double rad = acos(1.0 / 5.0) - M_PI;
    ATransform p2(AQuaternion(AVector3(0,0,1), rad), AVector3(2,0,0));
    ATransform p3(AQuaternion::Identity, AVector3(5,0,0));

    ATransform newPt;
    newPt = root * p2 * p3 * ATransform();

    std::cout << "new pt: " << newPt.translation << std::endl;
    std::cout << "length: " << newPt.translation.length() << std::endl;

    /*double theta1Z = asin(-sin(rad));
    std::cout << "theta 1z " << theta1Z << " " << theta1Z * ARad2Deg << std::endl;

    ATransform newPtAlongX;
    newPtAlongX = ATransform(AQuaternion(AVector3(0,0,1), theta1Z), root.translation) * p2 * p3 * ATransform();
    std::cout << "new point is " << newPtAlongX << std::endl;

    double beta = atan2(pd.z(), pd.x());
    std::cout << "beta is " << beta << std::endl;
    double gamma = asin(pd.y() / 5.0);
    std::cout << "gamma is " << gamma << std::endl;

    ATransform finalPt;
    ATransform finalPart1 = p2 * p3 * ATransform();

    AMatrix3 mat;
    mat.fromEulerAnglesYZX(AVector3(0, beta, gamma));
    AQuaternion quatPart2 = AQuaternion(mat) * AQuaternion(AVector3(0,0,1), theta1Z);

    ATransform finalPart2 = ATransform(quatPart2, root.translation);
    finalPt = finalPart2 * finalPart1;
    std::cout << "Final pt (polar)" << finalPt << std::endl;*/

    AVector3 dir = newPt.translation - root.translation;
    AVector3 error = pd - newPt.translation;
    std::cout << "error: " << error << std::endl;

    AVector3 cross = AVector3::Cross(dir, error);
    std::cout << "cross: " << cross << std::endl;

    AVector3 axis = cross / cross.length();
    std::cout << "axis: " << axis << std::endl;

    double phi = atan2(cross.length(), AVector3::Dot(dir,dir) + AVector3::Dot(dir,error));
    std::cout << "phi: " << phi << std::endl;

    ATransform finalPt = ATransform(AQuaternion(axis, phi), root.translation) * p2 * p3 * ATransform();
    std::cout << "final: " << finalPt << std::endl;

   AJoint* shoulder = new AJoint("Shoulder");
   mActor.addJoint(shoulder);
   shoulder->setLocalTranslation(AVector3(0,0,0));

   AJoint* elbow = new AJoint("Elbow");
   mActor.addJoint(elbow, shoulder);
   elbow->setLocalTranslation(AVector3(100,0,0));

   AJoint* wrist = new AJoint("Wrist");
   mActor.addJoint(wrist, elbow);
   wrist->setLocalTranslation(AVector3(80,0,0));

   mActor.fk();

   mGoalPosition = wrist->getGlobalTranslation();
   mSelectedJoint = 2;

   loadIKJoints();
}

AIKSimple::~AIKSimple()
{
}

void AIKSimple::initializeGui()
{
    mPoseEditBar = TwNewBar("Edit Pose");
    TwDefine(" 'Edit Pose' size='200 500' position='5 5' iconified=false fontresizable=false alpha=200");
    TwAddButton(mPoseEditBar, "Reset Pose", ResetIKCb, this, " ");
    TwAddVarCB(mPoseEditBar, "X", TW_TYPE_DOUBLE, onSetGoalXCb, onGetGoalXCb, this, " group='Goal position'");
    TwAddVarCB(mPoseEditBar, "Y", TW_TYPE_DOUBLE, onSetGoalYCb, onGetGoalYCb, this, " group='Goal position'");
    TwAddVarCB(mPoseEditBar, "Z", TW_TYPE_DOUBLE, onSetGoalZCb, onGetGoalZCb, this, " group = 'Goal position'");

   loadIKJoints();
}

void AIKSimple::reset()
{
    AMatrix3 identity;
    identity.fromEulerAnglesXYZ(AVector3(0,0,0));
    for (int i = 0; i < mActor.getNumJoints(); i++)
	 {
       mActor.getByID(i)->setLocalRotation(identity);
	 }
    mActor.fk();
    mGoalPosition = mActor.getByID(2)->getGlobalTranslation();
    glutPostRedisplay();
}

void AIKSimple::update() // assumes joint already chosen
{
    mController.solveIKTwoLink(mActor, mGoalPosition);
}

void AIKSimple::draw()
{
    mDrawer.draw(mActor);
    drawOverlay();
}

void DrawCircle(const AVector3& p)
{
    int vertices = 20;
    double r = 5.0;
    double tmpX, tmpY, tmpZ;
    double Angle, Angle0;

    Angle = -(2 * 3.14) / vertices;
    Angle0 = 0.0;

    tmpX = p[0];
    tmpY = p[1];
    tmpZ = p[2];

    glBegin(GL_LINE_LOOP);

    for (int i = 0; i < vertices; i++) {
        glVertex3f(tmpX + r * cos(i*Angle + Angle0), tmpY + r * sin(i*Angle + Angle0), tmpZ);
    }
    glEnd();
}

void AIKSimple::drawOverlay()
{
    int screenX, screenY;
    getCamera()->worldToScreen(mGoalPosition, screenX, screenY);

    glColor3f(1.0, 0.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, getWidth(), 0, getHeight());
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    DrawCircle(AVector3(screenX, screenY, 0));
    glBegin(GL_LINES);
    glVertex3f(screenX + 10.0, screenY, 0);
    glVertex3f(screenX - 10.0, screenY, 0);
    glVertex3f(screenX, screenY + 10.0, 0);
    glVertex3f(screenX, screenY - 10.0, 0);
    glEnd();
    glPopMatrix();
}

void TW_CALL AIKSimple::ResetIKCb(void* clientData)
{
    AIKSimple* viewer = (AIKSimple*)clientData;
    viewer->reset();
}

void AIKSimple::loadIKJoints()
{
    for (int i = 0; i < (int) mEffectorData.size(); i++)
    {
        TwRemoveVar(mPoseEditBar, mEffectorData[i]->name.c_str());
        delete mEffectorData[i];
    }
    mEffectorData.clear();

    char buff[256];
    for (int i = 0; i < mActor.getNumJoints(); i++)
    {
        AJoint* joint = mActor.getByID(i);
        if (joint->getParent() &&
            joint->getParent()->getName().find("Hand") != std::string::npos)
        {
            continue;
        }
        if (joint->getName().find("Site") != std::string::npos) continue;

        EffectorData* ld = new EffectorData;
        ld->viewer = this;
        ld->jointid = i;
        ld->name = joint->getName();
        mEffectorData.push_back(ld);

        sprintf(buff, " label='%s' group='Select Joint'", joint->getName().c_str());
        TwAddButton(mPoseEditBar, mEffectorData.back()->name.c_str(), SelectIKCb, ld, buff);
    }
}


void AIKSimple::mouseMove(int pX, int pY)
{
    if (mModifierState == GLUT_ACTIVE_CTRL && mSelectedJoint > -1 && mButtonState == GLUT_LEFT_BUTTON)
    {
        //std::cout << pX << " " << pY << std::endl;
        if (mSelectedRecticle) // update pos with new p
        {
            double dsqr = AVector3::DistanceSqr(
                AVector3(mLastIKX, getHeight() - mLastIKY, 0), 
                AVector3(pX, pY, 0));
            //std::cout << dsqr << std::endl;
            if (dsqr > 300.0)
            {
                AVector3 target(0, 0, 0);
                AVector3 current(0, 0, 0);
                getCamera()->screenToWorld(mLastIKX, 
                    getHeight() - mLastIKY, current);
                getCamera()->screenToWorld(pX, getHeight() - pY, target);

                // Did we click on the IK sphere previously?
                AVector3 eye = getCamera()->getPosition();

                double distToScreen = AVector3::Distance(eye, current);
                double distToScreenTarget = AVector3::Distance(current, target);
                double distToObject = AVector3::Distance(eye, mGoalPosition);
                double distToTarget = distToObject*
                    distToScreenTarget / distToScreen; // similar triangles

                AVector3 dir = target - current;
                dir.normalize();
                dir = dir * distToTarget;
                mGoalPosition = mGoalPosition + dir;

                update();
                mLastIKX = pX; 
                mLastIKY = pY;
            }
        }
    }

    mLastX = pX;
    mLastY = pY;
}

void AIKSimple::mousePress(int pButton, int pState, int pX, int pY)
{
    mModifierState = pState;
    mButtonState = pButton;
    if (mModifierState == GLUT_ACTIVE_CTRL && mSelectedJoint > -1)
    {
        int screenX, screenY;
        getCamera()->worldToScreen(mGoalPosition, screenX, screenY);

        double d = (screenX - pX)*(screenX - pX) + 
            (screenY - getHeight() + pY)*(screenY - getHeight() + pY);
        mSelectedRecticle = (d <= 100);  // recticle has radius 5 in screen space

        mLastIKX = pX;
        mLastIKY = pY;
    }
    else
    {
        mSelectedRecticle = false;
    }
}

void TW_CALL AIKSimple::onSetGoalXCb(const void *value, void *clientData)
{
    AIKSimple* viewer = ((AIKSimple*)clientData);
    double v = *(const double *)value;  // for instance
    viewer->mGoalPosition[0] = v;
    viewer->update();
}

void TW_CALL AIKSimple::onGetGoalXCb(void *value, void *clientData)
{
    AIKSimple* viewer = ((AIKSimple*)clientData);
    *static_cast<double *>(value) = viewer->mGoalPosition[0];
}

void TW_CALL AIKSimple::onSetGoalYCb(const void *value, void *clientData)
{
    AIKSimple* viewer = ((AIKSimple*)clientData);
    double v = *(const double *)value;  // for instance
    viewer->mGoalPosition[1] = v;
    viewer->update();
}

void TW_CALL AIKSimple::onGetGoalYCb(void *value, void *clientData)
{
    AIKSimple* viewer = ((AIKSimple*)clientData);
    *static_cast<double *>(value) = viewer->mGoalPosition[1];
}

void TW_CALL AIKSimple::onSetGoalZCb(const void *value, void *clientData)
{
    AIKSimple* viewer = ((AIKSimple*)clientData);
    double v = *(const double *)value;  // for instance
    viewer->mGoalPosition[2] = v;
    viewer->update();
}

void TW_CALL AIKSimple::onGetGoalZCb(void *value, void *clientData)
{
    AIKSimple* viewer = ((AIKSimple*)clientData);
    *static_cast<double *>(value) = viewer->mGoalPosition[2];
}

void TW_CALL AIKSimple::SelectIKCb(void* clientData)
{
    EffectorData* data = (EffectorData*)clientData;
    AIKSimple* viewer = data->viewer;
    int jointid = data->jointid;
    std::string name = data->name;

    //std::cout << "Select joint: " << name.c_str() << std::endl;
    viewer->onSelectIKJoint(jointid);
}

void AIKSimple::setGoalPosition(const AVector3& pos) 
{
    mGoalPosition = pos;
    update();
}

AVector3 AIKSimple::getSelectedPosition() const 
{
    if (mSelectedJoint == -1) return AVector3::Zero;
    return mActor.getByID(mSelectedJoint)->getGlobalTranslation();
}

void AIKSimple::setSelectedJoint(const std::string& name)
{
    AJoint* joint = mActor.getByName(name);
    if (joint) mSelectedJoint = joint->getID();
    else std::cout << "Invalid joint name: " << name << std::endl;
}

std::string AIKSimple::getSelectedJoint() const
{
    AJoint* joint = mActor.getByID(mSelectedJoint);
    if (joint) return joint->getName();
    return "NotSelected";
}


