set(SRC 
   AFramework.cpp  
   AApp.cpp  
   AApp2D.cpp  
   AApp3D.cpp  
   AUiTimeBar.cpp  
   AUiDirBar.cpp  
   ASkeletonDrawer.cpp  
   ACamera.cpp	  
   ATimer.cpp
   AOsUtils.cpp
   )

if (WIN32)
  add_library(ui STATIC ${SRC})
elseif (UNIX)
add_library(ui SHARED ${SRC})
endif()

