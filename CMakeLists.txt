cmake_minimum_required(VERSION 3.20.0)
project(aoc22)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR})

set(SOURCES
    main.cpp
    solution1.cpp
    solution2.cpp
    
    utils/read_utils.cpp
)

set(INPUTS
    inputs/input1.txt
    inputs/input2.txt
)

add_executable(aoc22 ${SOURCES})

install(TARGETS aoc22 RUNTIME DESTINATION "install" )
install(FILES ${INPUTS} DESTINATION "install/inputs")