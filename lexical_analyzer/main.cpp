//
// Created by Dell on 03/12/2023.
//

#include <iostream>
#include "ThomsonConstructor.h"
#include "NFA.h"
#include "RegexParser.h"
#include "State.h"
#include "Utility.h"
#include "PriorityTable.h"
#include "DFA.h"
#include "NfaToDfaConverter.h"

int main() {
    RegexParser regexParser;
    NFA* nfa = regexParser.parseREs("D:/Computer and Systems Engineering/7th Semster\\Compilers/Project/Compiler/lexical_analyzer/rules");
//    DFA *dfa = new DFA("1");
//    dfa->addTransition('e', *dfa);
}
