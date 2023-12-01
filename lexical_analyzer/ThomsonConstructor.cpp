//
// Created by Dell on 01/12/2023.
//

#include "ThomsonConstructor.h"

int ThomsonConstructor::id = 0;
char ThomsonConstructor::epsilon = '\0';

NFA ThomsonConstructor::creatBasic(char input) {
    State startState(to_string(id++));
    State endState(to_string(id++));
    startState.addTransition(input, endState);
    NFA nfa(startState, endState);
    return nfa;
}

NFA ThomsonConstructor::range(char src, char dest) {
    State startState(to_string(id++));
    State endState(to_string(id++));
    for (int i = int(src); i <= int(dest); i++)
        startState.addTransition((char)i, endState);
    NFA nfa(startState, endState);
    return nfa;
}

NFA ThomsonConstructor::union_(NFA nfa1, NFA nfa2) {
    State startState(to_string(id++));
    State endState(to_string(id++));
    startState.addTransition(epsilon, nfa1.startState);
    startState.addTransition(epsilon, nfa2.startState);
    nfa1.endState.addTransition(epsilon, endState);
    nfa2.endState.addTransition(epsilon, endState);
    NFA nfa(startState, endState);
    return nfa;
}

NFA ThomsonConstructor::concat(NFA nfa1, const NFA& nfa2) {
    nfa1.endState.addTransition(epsilon, nfa2.startState);
    NFA nfa(nfa1.startState, nfa2.endState);
    return nfa;
}

NFA ThomsonConstructor::kleenClosure(NFA nfa) {
    State startState(to_string(id++));
    State endState(to_string(id++));
    nfa.endState.addTransition(epsilon, nfa.startState);
    startState.addTransition(epsilon, nfa.startState);
    nfa.endState.addTransition(epsilon, endState);
    startState.addTransition(epsilon, endState);
    NFA newNFA(startState, endState);
    return newNFA;
}

NFA ThomsonConstructor::positiveClosure(const NFA& nfa) {
    return concat(nfa, kleenClosure(nfa));
}
