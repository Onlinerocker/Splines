add_executable(a3-curveEditor ACurveEditor.cpp curveEditor.cpp)
target_link_libraries(a3-curveEditor ${LIBS})

add_executable(a3-testCatmullRom testCatmullRom.cpp)
target_link_libraries(a3-testCatmullRom ${LIBS})

add_executable(a3-testHermite testHermite.cpp)
target_link_libraries(a3-testHermite ${LIBS})

add_executable(a3-solveEqn solveEqn.cpp)
target_link_libraries(a3-solveEqn ${LIBS})

add_executable(a3-hermiteEx hermiteEx.cpp)
target_link_libraries(a3-hermiteEx ${LIBS})
