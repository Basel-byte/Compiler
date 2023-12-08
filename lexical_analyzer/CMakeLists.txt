cmake_minimum_required(VERSION 3.22)
project(Compiler)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Compiler
        NFA.cpp
        NfaToDfaConverter.cpp
        State.cpp
        NfaToDfaConverter.cpp
        PriorityTable.cpp
        ThomsonConstructor.cpp
        RegexParser.cpp
        Utility.cpp
        DFA.cpp
        main.cpp
        LexicalParser.cpp
        DFAMinimization.cpp
        TransitionTableWriter.cpp
        )
