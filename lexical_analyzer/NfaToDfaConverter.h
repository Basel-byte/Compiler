//
// Created by mai on 12/1/23.
//

#ifndef COMPILER_NFATODFACONVERTER_H
#define COMPILER_NFATODFACONVERTER_H


#include "State.h"
#include "PriorityTable.h"
#include "DFA.h"

class NfaToDfaConverter {
public:
    static vector<State*> getEpsilonClosure(State* state);
    static string getStateNewName(vector<State*> states);
    static void setAcceptingState(DFA* dfaState, const vector<State*>& nfaStates);
    static vector<DFA*> convertNFAToDFA(State startNFAState);

private:
    PriorityTable pTable;
};


#endif //COMPILER_NFATODFACONVERTER_H
