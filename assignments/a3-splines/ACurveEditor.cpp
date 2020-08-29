#include <string>
#include <iostream>
#include "ACurveEditor.h"
#include "AGLObjects.h"
#include <algorithm>
#include <AntTweakBar.h>

float timeElap;

ACurveEditor::ACurveEditor() : 
    AFramework(AFramework::Orthographic), 
    mSpline(),
    mRadius(5.0),
    mSelected(-1),
    mPickType(0),
    mButtonState(0),
    mModifierState(0),
    mMode(ADD), 
    mShowControlPoints(false)
{
}

ACurveEditor::~ACurveEditor()
{
}

//Draws spline from normalized time [0, 1]
void ACurveEditor::drawCurve()
{
    //For each small time interval, draw the line at its calculated position
    for(double x=0; x<=mSpline.getDuration()-0.001; x+=0.001){
        AVector3 pt = mSpline.getValue(x, true);
        ASetColor(AVector3(1,0,0));
        ADrawLine(pt, mSpline.getValue(x+0.001, true));
    }

    ASetColor(AVector3(0,1,0));
    ADrawSphere(mSpline.getValue(timeElap, true), 5);
}

void ACurveEditor::update()
{
    //Increment the elapsed time with delta time
    timeElap += dt();
    
    //If the time is greater than the total duration
    //reset the elapsed time to zero
    if(timeElap > mSpline.getDuration())
        timeElap = 0;

}

void ACurveEditor::draw()
{
   //Return if there isn't enough key points
   if (mSpline.getNumKeys() < 1) return;

   //If only one key, just draw that
   if (mSpline.getNumKeys() == 1)
   {
      glColor3f(0.0, 0.0, 1.0);
      drawCircle(mSpline.getKey(0));
      return;
   }

   drawCurve(); //Draw the curve

   std::string type = mSpline.getInterpolationType();
   if (type == "Hermite")
   {
      for (int i = 0; i < mSpline.getNumControlPoints(); i+=2)
      {
         AVector3 key = mSpline.getControlPoint(i);
         glColor3f(0.0, 0.0, 1.0);
         drawCircle(key);

         if (mShowControlPoints)
         {
            AVector3 slope = mSpline.getControlPoint(i+1);
            glColor3f(1.0, 1.0, 0.0);
            drawCircle(key + slope);
            ADrawLine(key, key+slope);
         }
      }
   }
   else if (type == "Linear")
   {
       //No control points, just draw the key points for linear
       for (int i = 0; i < mSpline.getNumKeys(); i++)
       {
           glColor3f(0.0, 0.0, 1.0);
           AVector3 pt = mSpline.getKey(i);
           drawCircle(pt);
       }
   }
   else if (type == "Catmull-Rom")
   {
      for (int i = 0; i < mSpline.getNumSegments() && mSpline.getNumControlPoints() > 0; i++)
      {
	 //Get the key points, set color, and draw them
         AVector3 b0 = mSpline.getControlPoint(i, 0);
         AVector3 b3 = mSpline.getControlPoint(i, 3);
         glColor3f(0.0, 0.0, 1.0);
         drawCircle(b0);
         drawCircle(b3);

         if (mShowControlPoints)
         {
            //Get each control point and set their color
            AVector3 b1 = mSpline.getControlPoint(i, 1);
            AVector3 b2 = mSpline.getControlPoint(i, 2);
            glColor3f(1.0, 1.0, 0.0);
            
	    //Draw each control point...
	    drawCircle(b1);
            drawCircle(b2);

	    //Draw lines between control points...
            ADrawLine(b0, b1);
            ADrawLine(b1, b2);
            ADrawLine(b2, b3);
         }
      }
   }
   glColor3f(1,1,0);
   drawCircle(mDot);
}

void ACurveEditor::drawCircle(const AVector3& p)
{
    int vertices = 20;
    double r = mRadius;
    double angle = -(2 * 3.14) / vertices;

    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(p[0], p[1], 0);
    for (int i = 0; i < vertices+1; i++) 
    {
        double x = p[0] + r * cos(-i*angle);
        double y = p[1] + r * sin(-i*angle);
        glVertex3f(x, y, 0);
    }
    glEnd();
}

void ACurveEditor::initializeGui()
{
    mCurveBar = TwNewBar("Curve controls");
    TwDefine(" 'Curve controls' size='200 175' position='5 5' iconified=false fontresizable=false alpha=200");
    TwEnumVal curveTypeEV[] = 
    { 
        { 0, "Linear" },
        { 1, "Catmull-Rom" },
        { 2, "Hermite" } 
    };
    curveType = TwDefineEnum("CurveType", curveTypeEV, 3);
    TwAddVarCB(mCurveBar, "Type", curveType, onSetStyleCb, onGetStyleCb, this, " ");

    TwEnumVal modeTypeEV[] = { { ADD, "Add" }, { EDIT, "Edit" }, { REMOVE, "Delete" } };
    modeType = TwDefineEnum("ModeType", modeTypeEV, 3);
    TwAddVarRW(mCurveBar, "Mode", modeType, &mMode, NULL);

    TwAddVarRW(mCurveBar, "Ctrl pts", TW_TYPE_BOOLCPP, &mShowControlPoints, "");
    TwAddButton(mCurveBar, "ClearBtn", onClearCb, this, " label='Clear'");
}

void ACurveEditor::mouseMove(int pX, int pY)
{
    if (mMode == EDIT && mButtonState == GLUT_LEFT_BUTTON)
    {
        movePicked(pX, getHeight() - pY);
    }

    glutPostRedisplay();
}

void ACurveEditor::movePicked(int x, int y)
{
    if (mSelected != -1)
    {
        AVector3 temp(x, y, 0);        
        if (mPickType == 0) 
        {
            mSpline.editKey(mSelected, temp);
        }
        else 
        {
            std::string type = mSpline.getInterpolationType();
            if (type == "Hermite")
            {
               temp -= mSpline.getControlPoint(mSelected-1); 
            }
            mSpline.editControlPoint(mSelected, temp);
        }
    }
}

void ACurveEditor::addPoint(int x, int y)
{
    AVector3 tmp(x, y, 0);
    // guard against adding multiple copies of the same point
    // (multiple mouse events may be triggered for the same point)
    if (mSpline.getNumKeys() > 0) 
    {
        AVector3 lastKey = mSpline.getKey(mSpline.getNumKeys() - 1);
        if ((lastKey-tmp).length() < 10) return;
    }

    //std::cout << "Add key: " << tmp << std::endl;
    mSpline.appendKey(mSpline.getNumKeys(), tmp);
}

void ACurveEditor::deletePoint(int x, int y)
{
    mSelected = -1;
    AVector3 tmp = AVector3(x, y, 0);

    // check data points -- needs to be done before ctrl points
    for (int i = 0; i < mSpline.getNumKeys(); i++)
    {
        AVector3 pt = mSpline.getKey(i);
        if ((tmp - pt).length() < mRadius)
        {
            mSpline.deleteKey(i);
            break;
        }
    }
}


void ACurveEditor::pickPoint(int x, int y)
{
    mSelected = -1;
    AVector3 tmp = AVector3(x, y, 0);

    // check data points -- needs to be done before ctrl points
    for (int i = 0; mSelected == -1 && i < mSpline.getNumKeys(); i++)
    {
        AVector3 pt = mSpline.getKey(i);
        if ((tmp - pt).length() < mRadius)
        {
            mPickType = 0;
            mSelected = i;
        }
    }

    // Check control points
    if (mSelected == -1)
    {
        std::string type = mSpline.getInterpolationType();
        if (type == "Hermite")
        {
           for (int i = 1; i < mSpline.getNumControlPoints(); i+=2)
           {
               AVector3 slope = mSpline.getControlPoint(i);
               AVector3 pt = mSpline.getControlPoint(i-1) + slope;
               if ((tmp - pt).length() < mRadius)
               {
                   mPickType = 1;
                   mSelected = i;
                   break;
               }
           }
        }
        else
        {
           for (int i = 0; i < mSpline.getNumControlPoints(); i++)
           {
               AVector3 pt = mSpline.getControlPoint(i);
               if ((tmp - pt).length() < mRadius)
               {
                   mPickType = 1;
                   mSelected = i;
                   break;
               }
           }
        }
    }
}

void ACurveEditor::mousePress(int pButton, int pState, int pX, int pY)
{
    mButtonState = pButton;
    mModifierState = glutGetModifiers();

    if (mButtonState == GLUT_LEFT_BUTTON)
    {
        if (mMode == ADD)
        {
            addPoint(pX, getHeight()-pY);
            glutPostRedisplay();
        }
        else if (mMode == REMOVE)
        {
            deletePoint(pX, getHeight() - pY);
            glutPostRedisplay();
        }
        else
        {
            pickPoint(pX, getHeight() - pY);
            mouseMove(pX, pY);
        }
    }

}

void ACurveEditor::keyPress(unsigned char pKey, int specialKey, int x, int y)
{
    if (pKey == 'p')
    {
       for (int i = 0; i < mSpline.getNumKeys(); i++)
		 {
           std::cout << mSpline.getKey(i) << std::endl;
		 }
    }
}

void ACurveEditor::onClearCb(void* usr)
{
   ((ACurveEditor*)usr)->mSpline.clear();
}

void TW_CALL ACurveEditor::onSetStyleCb(const void *value, void *clientData)
{
   ACurveEditor* viewer = ((ACurveEditor*)clientData);
   int v = *(int*)value;  
   std::string type = viewer->mSpline.getInterpolationType();
   switch(v)
   {
   case 0: type = "Linear"; break;
   case 1: type = "Catmull-Rom"; break;
   case 2: type = "Hermite"; break;
   }
   viewer->mSpline.setInterpolationType(type);
}

void TW_CALL ACurveEditor::onGetStyleCb(void *value, void *clientData)
{
   ACurveEditor* viewer = ((ACurveEditor*)clientData);
   std::string type = viewer->mSpline.getInterpolationType();
   if (type == "Linear") *((int*)value) = 0;
   else if (type == "Catmull-Rom") *((int*)value) = 1;
   else if (type == "Hermite") *((int*)value) = 2;
}

