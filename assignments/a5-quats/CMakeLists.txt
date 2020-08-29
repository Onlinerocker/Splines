include_directories(
   ../../libsrc/animation 
   ../../libsrc/ui 
   ../3rdparty/AntTweakBar/include 
   /usr/include/eigen3)

link_directories(
   ../lib 
   /usr/local/lib
   /usr/X11R6/lib 
   libsrc/animation 
   libsrc/ui 
   ../3rdparty/AntTweakBar/lib)

add_executable(a5-ripples Ripples.cpp)

target_link_libraries(a5-ripples
   ui animationbasic animationfk AntTweakBar GLEW 
   glut GL GLU X11)

add_executable(a5-testQuat testQuat.cpp)
target_link_libraries(a5-testQuat animationbasic animationfk)

add_executable(a5-testQuatMat testQuatMat.cpp)
target_link_libraries(a5-testQuatMat animationbasic animationfk)
