cmake_minimum_required(VERSION 3.22)
project(Compiler)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

enable_testing()
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

add_executable(lf_test tests/lf_test.cpp)

target_include_directories(lf_test
        PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/lexical_analyzer
        PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/syntax_analyzer)

target_link_libraries(lf_test
        PRIVATE lexical_analyzer
        PRIVATE syntax_analyzer)

add_test(NAME left_refactoring_test1
         COMMAND lf_test ../syntax_analyzer/SampleTests/rules/simple_examples/simple_rules_3.txt)

add_test(NAME left_refactoring_test2
        COMMAND lf_test ../syntax_analyzer/SampleTests/rules/simple_examples/simple_rules_4.txt)

add_test(NAME left_refactoring_test3
        COMMAND lf_test ../syntax_analyzer/SampleTests/rules/simple_examples/simple_rules_5.txt)