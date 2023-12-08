//
// Created by Habiba on 12/4/2023.
//

#ifndef COMPILER_DFAMINIMIZATION_H
#define COMPILER_DFAMINIMIZATION_H


#include "State.h"
#include "NfaToDfaConverter.h"
#include "DFA.h"

class DFAMinimization {
public:
    static set<DFA*> minimization(vector<DFA*>);

    static string minimizedStateName(set<DFA*>);

    static void setAcceptingMinimizedStateDFA(DFA*,set<DFA*>);

    static set<DFA*> minimizeHelper(set<set<DFA*>>);

    static bool compareDFAId(DFA *i1, DFA *i2);

    static DFA* getStartState(set<DFA*> &dfas);
};

#endif //COMPILER_DFAMINIMIZATION_H
