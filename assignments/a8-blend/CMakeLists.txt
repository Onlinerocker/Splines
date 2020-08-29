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

add_executable(a8-crossfade ACrossfadeViewer.cpp ACrossfadeMain.cpp)
target_link_libraries(a8-crossfade ${LIBS})

add_executable(a8-reorient AReorient.cpp )
target_link_libraries(a8-reorient ${LIBS})

add_executable(a8-zombie AZombieArms.cpp )
target_link_libraries(a8-zombie ${LIBS})

add_executable(a8-blend ABlend.cpp )
target_link_libraries(a8-blend ${LIBS})

add_executable(a8-splice ASplice.cpp )
target_link_libraries(a8-splice ${LIBS})
