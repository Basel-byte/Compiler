cmake_minimum_required(VERSION 3.22)
project(Compiler)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Compiler
        NFA.cpp
        NFA.h
        State.cpp
        State.h
        PriorityTable.cpp
        PriorityTable.h)
