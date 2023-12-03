cmake_minimum_required(VERSION 3.22)
project(Compiler)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Compiler
        NFA.cpp
        NFA.h
        NfaToDfaConverter.cpp
        NfaToDfaConverter.h
        State.cpp
        State.h
        NfaToDfaConverter.cpp
        NfaToDfaConverter.h
        PriorityTable.cpp
        PriorityTable.h
        ThomsonConstructor.cpp
        ThomsonConstructor.h
        RegexParser.cpp
        RegexParser.h
        Utility.cpp
        Utility.h
        DFA.cpp
        DFA.h
        main.cpp)