//
// Created by Dell on 01/12/2023.
//

#ifndef COMPILER_UTILITY_H
#define COMPILER_UTILITY_H


#include "NFA.h"

class Utility {
public:
    static NFA* getCorrespondingNFA(vector<pair<char, NFA*>> infix);
private:
    static vector<pair<char, NFA*>> infixToPostfix(const vector<pair<char, NFA*>>& infix);
    static NFA *doOperation(char c, NFA *nfa1, NFA *nfa2);
    static int getPrecedence(char c);
    static bool isUnary(char c);
};


#endif //COMPILER_UTILITY_H
