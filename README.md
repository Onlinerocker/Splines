# Spline Curve Editor
**Name** \
Gabriel Caldwell

**Structure** \
During my Computer Animation course I developed key animation library features, and implemented those features into various applications. Application specific code can be found in *assignments* and library code can be found in *libsrc/animation*.

Project dependencies are located in *3rdparty*. You shouldn't need to touch these.

For this assignment, the code I developed can be found in:
* *assignments/a3-splines/ACurveEditor.cpp*
* *libsrc/animation/AInterpolator-basecode.cpp*

**The Functions I developed:**\
\
*ACurveEditor*
* drawCurve
* update

*AInterpolator-basecode*
* AInterpolatorLinear::interpolate
* AInterpolatorLinear::computeControlPoints
* AInterpolatorCatmullRom::interpolate
* AInterpolatorCatmullRom::computeControlPoints
* AInterpolatorHermite::interpolate
* AInterpolatorHermite::computeControlPoints

**Description** \
This spline curve editor was created during my Computer Animation course at Swarthmore College. The goal was to create an interactive way to learn about different types of splines/interpolation. I implemented functions to calculate control points for Catmul-Rom and Hermite Splines respectively. Additionally, I developed functions to interpolate a point across each spline. 

**Originally Created** \
September 27, 2019


**Windows Build Instructions** \
Requirements: CMake, Visual Studio
* Create new directory named 'build' in the project's root directory
* Navigate to this new directory and run 'cmake -A Win32 ..'
* This should build the required files
* Open 'build/Project.sln' in Visual Studio
* In the Solution Explorer, right click 'INSTALL', then click 'Build'
* You should now have a 'bin' folder in the project's root directory
* Navigate to 'bin/Debug' and run 'a3-curveEditor.exe'
