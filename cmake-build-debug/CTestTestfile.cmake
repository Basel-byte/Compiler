# CMake generated Testfile for 
# Source directory: /home/basel/Projects/Compiler
# Build directory: /home/basel/Projects/Compiler/cmake-build-debug
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test([=[left_refactoring_test1]=] "/home/basel/Projects/Compiler/cmake-build-debug/lf_test" "../syntax_analyzer/SampleTests/rules/simple_examples/simple_rules_3.txt")
set_tests_properties([=[left_refactoring_test1]=] PROPERTIES  _BACKTRACE_TRIPLES "/home/basel/Projects/Compiler/CMakeLists.txt;32;add_test;/home/basel/Projects/Compiler/CMakeLists.txt;0;")
add_test([=[left_refactoring_test2]=] "/home/basel/Projects/Compiler/cmake-build-debug/lf_test" "../syntax_analyzer/SampleTests/rules/simple_examples/simple_rules_4.txt")
set_tests_properties([=[left_refactoring_test2]=] PROPERTIES  _BACKTRACE_TRIPLES "/home/basel/Projects/Compiler/CMakeLists.txt;35;add_test;/home/basel/Projects/Compiler/CMakeLists.txt;0;")
add_test([=[left_refactoring_test3]=] "/home/basel/Projects/Compiler/cmake-build-debug/lf_test" "../syntax_analyzer/SampleTests/rules/simple_examples/simple_rules_5.txt")
set_tests_properties([=[left_refactoring_test3]=] PROPERTIES  _BACKTRACE_TRIPLES "/home/basel/Projects/Compiler/CMakeLists.txt;38;add_test;/home/basel/Projects/Compiler/CMakeLists.txt;0;")
subdirs("lexical_analyzer")
subdirs("syntax_analyzer")
