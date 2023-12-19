cmake_minimum_required(VERSION 3.22)
project(Compiler)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(lexical_analyzer)
add_subdirectory(syntax_analyzer)

add_executable(compiler
        main.cpp)

target_include_directories(compiler
        PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/lexical_analyzer
        PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/syntax_analyzer)

target_link_libraries(compiler
        PRIVATE lexical_analyzer
        PRIVATE syntax_analyzer)