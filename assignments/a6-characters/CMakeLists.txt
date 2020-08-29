add_executable(a6-testSlerp testSlerp.cpp)
target_link_libraries(a6-testSlerp ${LIBS})

add_executable(a6-boxes boxes.cpp)
target_link_libraries(a6-boxes ${LIBS})

add_executable(a6-slerpTeapot ASlerpTeapot.cpp)
target_link_libraries(a6-slerpTeapot ${LIBS})

add_executable(a6-testTransform testTransform.cpp)
target_link_libraries(a6-testTransform ${LIBS})

add_executable(a6-skeleton ASkeletonPractice.cpp)
target_link_libraries(a6-skeleton ${LIBS})

add_executable(a6-cone AKeyframeCone.cpp)
target_link_libraries(a6-cone ${LIBS})

add_executable(a6-tentacle ATentacle.cpp)
target_link_libraries(a6-tentacle ${LIBS})
