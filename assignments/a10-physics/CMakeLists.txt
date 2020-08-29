include_directories(
   ../../libsrc/animation 
   ../../libsrc/ui 
   ../3rdparty/AntTweakBar/include /usr/include/eigen3)

link_directories(../lib /usr/X11R6/lib libsrc/animation 
    libsrc/ui ../3rdparty/AntTweakBar/lib)

add_executable(a10-boxSim1 ABoxSim1.cpp)
target_link_libraries(a10-boxSim1 ui animationik animationfk
    animationbasic animationspline AntTweakBar GLEW glut GL GLU X11 ode pthread)

add_executable(a10-boxSim2 ABoxSim2.cpp)
target_link_libraries(a10-boxSim2 ui animationik animationfk
    animationbasic animationspline AntTweakBar GLEW glut GL GLU X11 ode pthread)

add_executable(a10-boxSim3 ABoxSim3.cpp)
target_link_libraries(a10-boxSim3 ui animationik animationfk
    animationbasic animationspline AntTweakBar GLEW glut GL GLU X11 ode pthread)

add_executable(a10-forces forces.cpp)
target_link_libraries(a10-forces ui animationik animationfk
    animationbasic animationspline AntTweakBar GLEW glut GL GLU X11 ode pthread)

add_executable(a10-unstoppable unstoppable.cpp)
target_link_libraries(a10-unstoppable animationik animationfk
    animationbasic ui AntTweakBar GLEW glut GL GLU X11 ode pthread)

add_executable(a10-fireworks fireworks.cpp)
target_link_libraries(a10-fireworks ui animationik animationfk
    animationbasic AntTweakBar GLEW glut GL GLU X11 ode pthread)

add_executable(a10-behaviors 
   AWorld.cpp ABehaviorViewer.cpp ASteerable.cpp ABehaviors.cpp)
target_link_libraries(a10-behaviors animationik animationfk
    animationbasic ui AntTweakBar GLEW glut GL GLU X11 ode pthread)

#add_executable(a10-skin skin.cpp)
#target_link_libraries(a10-skin animationik animationfk
    #animationbasic ui AntTweakBar GLEW glut GL GLU X11 ode pthread)
