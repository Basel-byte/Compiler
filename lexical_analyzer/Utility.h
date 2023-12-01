//
// Created by Dell on 01/12/2023.
//

#ifndef COMPILER_UTILITY_H
#define COMPILER_UTILITY_H


#include "NFA.h"

class Utility {
public:
    static NFA creatBasic(char input);
    static NFA range(char src, char dest);
    static NFA union_(NFA nfa1, NFA nfa2);
    static NFA concat(NFA nfa1, const NFA& nfa2);
    static NFA kleenClosure(NFA nfa);
    static NFA positiveClosure(const NFA& nfa);
public:
    static int id;
};


#endif //COMPILER_UTILITY_H
