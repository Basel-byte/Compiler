//
// Created by mai on 12/1/23.
//

#ifndef COMPILER_DFA_H
#define COMPILER_DFA_H


#include "State.h"
#include "PriorityTable.h"
#include "DFAState.h"

class DFA {
public:
    static vector<State*> getEpsilonClosure(State* state);
    static string getStateNewName(vector<State*> states);
    static void setAcceptingState(DFAState* dfaState, const vector<State*>& nfaStates);
    static vector<DFAState*> convertNFAToDFA(State startNFAState);

private:
    PriorityTable pTable;
};


#endif //COMPILER_DFA_H
