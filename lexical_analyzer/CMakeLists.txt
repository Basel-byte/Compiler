cmake_minimum_required(VERSION 3.22)
project(LexicalAnalyzer)

set(CMAKE_CXX_STANDARD 14)

add_library(lexical_analyzer
        NFA.cpp
        NfaToDfaConverter.cpp
        NfaToDfaConverter.cpp
        State.cpp
        NfaToDfaConverter.cpp
        PriorityTable.cpp
        ThomsonConstructor.cpp
        RegexParser.cpp
        Utility.cpp
        DFA.cpp
        LexicalParser.cpp
        DFAMinimization.cpp
        TransitionTableWriter.cpp
        ../syntax_analyzer/FirstSet.cpp
        ../syntax_analyzer/ParsingTable.cpp
        ../syntax_analyzer/FollowSet.cpp)

target_include_directories(lexical_analyzer
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})