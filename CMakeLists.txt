cmake_minimum_required(VERSION 3.20.0)
project(aoc22)

set(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR})

set(SOURCES
    solution1.cpp
    read_utils.h
)

set(INPUTS
    inputs/input1.txt
)

add_executable(aoc22 ${SOURCES})

install(TARGETS aoc22 RUNTIME DESTINATION "install" )
install(FILES ${INPUTS} DESTINATION "install/inputs")