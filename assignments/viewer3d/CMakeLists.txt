include_directories(
   /usr/include/eigen3
   ../../libsrc/animation 
   ../../libsrc/ui 
   ../3rdparty/AntTweakBar/include)

link_directories(
   /usr/X11R6/lib 
   /usr/local/lib 
   libsrc/animation 
   libsrc/ui 
   ../3rdparty/AntTweakBar/lib)

add_executable(viewer3d 
   basicMain.cpp)

target_link_libraries(viewer3d 
   ui 
   animationbasic 
   animationfk 
   AntTweakBar 
   GLEW 
   glut 
   GL 
   GLU 
   X11)

