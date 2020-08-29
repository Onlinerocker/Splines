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

add_executable(a1-eyes eyes.cpp)
target_link_libraries(a1-eyes ${LIBS})

add_executable(a1-look look.cpp)
target_link_libraries(a1-look ${LIBS})

add_executable(a1-velocity velocity.cpp)
target_link_libraries(a1-velocity ${LIBS})

add_executable(a1-circles circles.cpp)
target_link_libraries(a1-circles ${LIBS})

add_executable(a1-particle particle.cpp)
target_link_libraries(a1-particle ${LIBS})

add_executable(a1-circle circle.cpp)
target_link_libraries(a1-circle ${LIBS})

add_executable(a1-bonus bonus.cpp)
target_link_libraries(a1-bonus ${LIBS})
