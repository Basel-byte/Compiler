//
// Created by Dell on 01/12/2023.
//

#include "Utility.h"

int Utility::id = 0;

NFA Utility::creatBasic(char input) {
    State startState(id++);
    State endState(id++);
    startState.addTransition(input, endState);
    NFA nfa(startState, endState);
    return nfa;
}

NFA Utility::range(char src, char dest) {
    State startState(id++);
    State endState(id++);
    for (int i = int(src); i <= int(dest); i++)
        startState.addTransition((char)i, endState);
    NFA nfa(startState, endState);
    return nfa;
}

NFA Utility::union_(NFA nfa1, NFA nfa2) {
    State startState(id++);
    State endState(id++);
    startState.addTransition('\0', nfa1.startState);
    startState.addTransition('\0', nfa2.startState);
    nfa1.endState.addTransition('\0', endState);
    nfa2.endState.addTransition('\0', endState);
    NFA nfa(startState, endState);
    return nfa;
}

NFA Utility::concat(NFA nfa1, const NFA& nfa2) {
    nfa1.endState.addTransition('\0', nfa2.startState);
    NFA nfa(nfa1.startState, nfa2.endState);
    return nfa;
}

NFA Utility::kleenClosure(NFA nfa) {
    State startState(id++);
    State endState(id++);
    nfa.endState.addTransition('\0', nfa.startState);
    startState.addTransition('\0', nfa.startState);
    nfa.endState.addTransition('\0', endState);
    startState.addTransition('\0', endState);
    NFA newNFA(startState, endState);
    return newNFA;
}

NFA Utility::positiveClosure(const NFA& nfa) {
    return concat(nfa, kleenClosure(nfa));
}
