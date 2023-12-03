//
// Created by Dell on 03/12/2023.
//
#include "RegexParser.h"
#include "iostream"
int main() {
    RegexParser regexParser;
    NFA* nfa = regexParser.parseREs("D:/Computer and Systems Engineering/7th Semster\\Compilers/Project/Compiler/lexical_analyzer/rules");
    return 0;
}