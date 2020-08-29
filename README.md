# Spline Curve Editor
**Name** \
Gabriel Caldwell

**Structure** \
The code I developed can be found in \
*assignments/a3-splines/ACurveEditor.cpp* \
*libsrc/animation/AInterpolator-basecode.cpp*.

**Description** \
This spline curve editor was created for one of my Computer Animation labs at Swarthmore College. I implemented functions to calculate control points for Catmul-Rom and Hermite Splines respectively. Additionally, I developed functions to interpolate a point across each spline. 

**Originally Created** \
September 27, 2019


**Windows Build Instructions** \
Requirements: CMake, Visual Studio
* Create new directory named 'build' in the project's root directory
* Navigate to this new directory and run 'cmake ..'
* This should build the required files
* Open 'build/Project.sln' in Visual Studio
* In the Solution Explorer, right click 'INSTALL', then click 'Build'
* You should now have a 'bin' folder in the project's root directory
* Navigate to 'bin/Debug' and run 'a3-curveEditor.exe'
