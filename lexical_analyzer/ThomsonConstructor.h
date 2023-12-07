//
// Created by Dell on 01/12/2023.
//

#ifndef COMPILER_THOMSONCONSTRUCTOR_H
#define COMPILER_THOMSONCONSTRUCTOR_H


#include "NFA.h"
#include "vector"

class ThomsonConstructor {
public:
    static NFA * createEpsilon();
    static NFA * creatBasic(char input);
    static NFA * range(char src, char dest);
    static NFA * union_(NFA nfa1, NFA nfa2);
    static NFA * concat(NFA nfa1, const NFA& nfa2);
    static NFA * kleenClosure(NFA nfa);
    static NFA * positiveClosure(const NFA& nfa);
    static NFA * getCombinedNFA(const vector<pair<string, NFA*>>& nfas);
private:
    static NFA * createNFA(vector<char> &inputs);
public:
    static int id;
    static char epsilon;
};


#endif //COMPILER_THOMSONCONSTRUCTOR_H
