cmake_minimum_required(VERSION 3.22)
project(SyntaxAnalyzer)

set(CMAKE_CXX_STANDARD 14)

add_library(syntax_analyzer
        FirstSet.cpp
        ParsingTable.cpp
        FollowSet.cpp
        CFGReader.cpp
        LeftRecursionEliminator.cpp
        NTSorter.cpp
        LeftFactorer.cpp
        SyntaxParser.cpp
        OUtil.cpp
        OUtil.h
)

target_include_directories(syntax_analyzer
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)