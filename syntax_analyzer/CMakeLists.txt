cmake_minimum_required(VERSION 3.22)
project(SyntaxAnalyzer)

set(CMAKE_CXX_STANDARD 14)

add_library(syntax_analyzer
        tmp.cpp
        FirstSet.cpp
        CFGReader.cpp
        LeftRecursionEliminator.cpp
        NTSorter.cpp
)

target_include_directories(syntax_analyzer
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})