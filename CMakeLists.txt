cmake_minimum_required(VERSION 3.20.0)
project(aoc22)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR})

set(SOURCES
    main.cpp

    solutions/solutions.cpp
    solutions/solution1.cpp
    solutions/solution2.cpp
    solutions/solution3.cpp
    solutions/solution4.cpp
    solutions/solution5.cpp
    solutions/solution6.cpp
    solutions/solution7.cpp
    solutions/solution8.cpp

    utils/read.cpp
)

set(INPUTS
    inputs/input1.txt
    inputs/input2.txt
    inputs/input3.txt
    inputs/input4.txt
    inputs/input5.txt
    inputs/input6.txt
    inputs/input7.txt
    inputs/input8.txt
)

add_executable(aoc22 ${SOURCES})

install(TARGETS aoc22 RUNTIME DESTINATION "install" )
install(FILES ${INPUTS} DESTINATION "install/inputs")