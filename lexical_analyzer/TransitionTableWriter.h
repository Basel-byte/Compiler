//
// Created by Dell on 08/12/2023.
//

#ifndef COMPILER_TRANSITIONTABLEWRITER_H
#define COMPILER_TRANSITIONTABLEWRITER_H


#include "DFA.h"
#include <set>

class TransitionTableWriter {
public:
    static void writeTableInTabularForm(set<DFA*> &dfa, string dirpath);
private:
    static void writeAcceptingStates(set<DFA*> &acceptingStates, string dirpath);
    static set<char> getInputs(vector<DFA *> &dfa);
};

#endif //COMPILER_TRANSITIONTABLEWRITER_H
