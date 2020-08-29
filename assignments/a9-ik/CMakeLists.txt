add_executable(a9-iksimple AIKSimple.cpp AIKSimpleMain.cpp)
target_link_libraries(a9-iksimple ${LIBS})

add_executable(a9-ik AIKViewer.cpp AIKSimple.cpp AIKMain.cpp)
target_link_libraries(a9-ik ${LIBS})

add_executable(a9-looker ALooker.cpp ACyclops.cpp)
target_link_libraries(a9-looker ${LIBS})

add_executable(a9-dancer ADancer.cpp ACyclops.cpp)
target_link_libraries(a9-dancer ${LIBS})
