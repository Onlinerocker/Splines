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

add_executable(a4-teapots
   teapots.cpp 
   ATeapotsViewer.cpp)

target_link_libraries(a4-teapots
   ui animationbasic animationfk AntTweakBar GLEW 
   glut GL GLU X11)

add_executable(a4-testEuler testEuler.cpp)
target_link_libraries(a4-testEuler animationbasic animationfk)

