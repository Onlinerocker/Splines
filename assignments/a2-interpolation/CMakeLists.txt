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

add_executable(a2-particleLerp particleLerp.cpp)
target_link_libraries(a2-particleLerp ${LIBS})

add_executable(a2-colorLerp1 colorLerp1.cpp)
target_link_libraries(a2-colorLerp1 ${LIBS})

add_executable(a2-colorLerp2 colorLerp2.cpp)
target_link_libraries(a2-colorLerp2 ${LIBS})

add_executable(a2-gradient gradient.cpp)
target_link_libraries(a2-gradient ${LIBS})

add_executable(a2-drawCubic drawCubic.cpp Cubic.cpp)
target_link_libraries(a2-drawCubic ${LIBS})

add_executable(a2-particleCubic particleCubic.cpp Cubic.cpp)
target_link_libraries(a2-particleCubic ${LIBS})

add_executable(a2-animateCubic animateCubic.cpp Cubic.cpp)
target_link_libraries(a2-animateCubic ${LIBS})

add_executable(a2-screensaver screensaver.cpp Cubic.cpp)
target_link_libraries(a2-screensaver ${LIBS})
