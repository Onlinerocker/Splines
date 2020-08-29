include_directories(
   /usr/include/eigen3
   ../../libsrc/animation
   ../../libsrc/ui
   ../../3rdparty/AntTweakBar/include)

link_directories(
   /usr/X11R6/lib
   /usr/local/lib
   libsrc/animation
   libsrc/ui
   3rdparty/AntTweakBar/lib)

set(LIBS ui animationbasic animationfk AntTweakBar GLEW glut GL GLU X11)

# C++ Practice

add_executable(a0-helloWorld c++/helloWorld.cpp)

# Viewer 2D Practice

add_executable(a0-greenSphere2d 2d/greenSphere2d.cpp)
target_link_libraries(a0-greenSphere2d ${LIBS})

add_executable(a0-redCube2d 2d/redCube2d.cpp)
target_link_libraries(a0-redCube2d ${LIBS})

# Viewer 3D Practice
add_executable(a0-greenSphere3d 3d/greenSphere3d.cpp)
target_link_libraries(a0-greenSphere3d ${LIBS})

add_executable(a0-redCube3d 3d/redCube3d.cpp)
target_link_libraries(a0-redCube3d ${LIBS})
