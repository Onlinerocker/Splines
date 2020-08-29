cmake_minimum_required(VERSION 2.8.11)

if (WIN32)

  find_library(GLUT NAMES glut32 PATHS 3rdparty/glut/glutx86)
  find_library(GLEW NAMES glew32 PATHS 3rdparty/glut/glutx86)
  find_library(AntTweakBar NAMES AntTweakBar PATHS 3rdparty/AntTweakBar.1.16/lib/)
  find_library(ODE NAMES ode_doubled PATHS 3rdparty/ode-0.13/lib/DebugDoubleDLL)
  include_directories(
     libsrc/animation
     libsrc/ui
     3rdparty/glut 
     3rdparty/AntTweakBar.1.16/include
     3rdparty/ode-0.13/include
     3rdparty/eigen-3.3.7)

  set(CMAKE_CXX_FLAGS 
     "/wd4018 /wd4244 /wd4305 
     /D_CRT_SECURE_NO_WARNINGS 
     /D_CRT_NONSTDC_NO_DEPRECATE 
     /D NOMINMAX
     /EHsc")

  set(CORE ${AntTweakBar} ${GLEW} ${GLUT})

  set(INSTALL_LIST
     3rdparty/glut/glutx86/glew32.dll 
     3rdparty/glut/glutx86/glut32.dll 
     3rdparty/AntTweakBar.1.16/lib/AntTweakBar.dll
     3rdparty/ode-0.13/lib/DebugDoubleDLL/ode_doubled.dll)
  install (FILES ${INSTALL_LIST} DESTINATION ${CMAKE_SOURCE_DIR}/bin/Debug)
  install (FILES ${INSTALL_LIST} DESTINATION ${CMAKE_SOURCE_DIR}/bin/Release)
  set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)

elseif (UNIX)

  set(CMAKE_CXX_FLAGS "-Wall -g -std=c++11 -DUNIX")
  set(OpenGL_GL_PREFERENCE "LEGACY")
  set(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/lib)
  set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)

  #for FindGLM.cmake, FindGLFW3.cmake, other helpers
  #set (CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake_modules) 

  #FIND_PACKAGE(OpenGL REQUIRED) 
  #FIND_PACKAGE(GLEW REQUIRED)
  #find_library(AntTweakBar NAMES AntTweakBar 
  #PATHS 3rdparty/AntTweakBar/lib/ ../3rdparty/AntTweakBar/lib /usr/local/lib)

  set(AntTweakBar 3rdparty/lib)

  include_directories(
    /usr/include/eigen3
    3rdparty/AntTweakBar/include
    3rdparty/gltf
    libsrc/animation
    libsrc/ui)

  link_directories(
    /usr/X11R6/lib
    /usr/local/lib
    libsrc/animation
    libsrc/ui
    3rdparty/AntTweakBar/lib)

  set(ODE ode pthread)
  set(CORE ${AntTweakBar} GLEW glut GL GLU X11)

endif()

add_subdirectory(assignments)
add_subdirectory(libsrc)
if (IS_DIRECTORY "${PROJECT_SOURCE_DIR}/test")
  add_subdirectory(test)
endif()
if (IS_DIRECTORY "${PROJECT_SOURCE_DIR}/examples")
  add_subdirectory(examples)
endif()
