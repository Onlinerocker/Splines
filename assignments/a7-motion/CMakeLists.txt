include_directories(
   ../../libsrc/animation 
   ../../libsrc/ui 
   /usr/include/eigen3 
   ../3rdparty/AntTweakBar/include)

link_directories(
   /usr/X11R6/lib 
   ../lib 
   libsrc/animation 
   libsrc/ui 
   ../3rdparty/AntTweakBar/lib)

set(LIBS ui animationblend animationfk animationbasic animationspline
   AntTweakBar GLEW glut GL GLU X11)

add_executable(a7-thriller AThriller.cpp)
target_link_libraries(a7-thriller ${LIBS}) 

add_executable(a7-motionviewer AFKViewer.cpp)
target_link_libraries(a7-motionviewer ${LIBS}) 

add_executable(a7-butterfly AButterfly.cpp)
target_link_libraries(a7-butterfly ${LIBS}) 

add_executable(a7-practice AMotionPractice.cpp) 
target_link_libraries(a7-practice ${LIBS}) 

add_executable(a7-fancy AFancy.cpp) 
target_link_libraries(a7-fancy ${LIBS}) 

add_executable(a7-controller AWASDSimple.cpp) 
target_link_libraries(a7-controller ${LIBS}) 
