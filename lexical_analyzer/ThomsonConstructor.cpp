//
// Created by Dell on 01/12/2023.
//

#include "ThomsonConstructor.h"

int ThomsonConstructor::id = 0;
char ThomsonConstructor::epsilon = '\0';

NFA* ThomsonConstructor::creatBasic(char input) {
    State startState(to_string(id++));
    State endState(to_string(id++));
    startState.addTransition(input, endState);
    NFA* nfa = new NFA(startState, endState);
    return nfa;
}

NFA* ThomsonConstructor::createEpsilon() {
    return creatBasic(epsilon);
}

NFA* ThomsonConstructor::range(char src, char dest) {
    State startState(to_string(id++));
    State endState(to_string(id++));
    for (int i = int(src); i <= int(dest); i++)
        startState.addTransition((char)i, endState);
    NFA* nfa = new NFA(startState, endState);
    return nfa;
}

NFA* ThomsonConstructor::union_(NFA nfa1, NFA nfa2) {
    State startState(to_string(id++));
    State endState(to_string(id++));
    startState.addTransition(epsilon, nfa1.startState);
    startState.addTransition(epsilon, nfa2.startState);
    nfa1.endState.addTransition(epsilon, endState);
    nfa2.endState.addTransition(epsilon, endState);
    NFA* nfa = new NFA(startState, endState);
    return nfa;
}

NFA* ThomsonConstructor::concat(NFA nfa1, const NFA& nfa2) {
    nfa1.endState.addTransition(epsilon, nfa2.startState);
    NFA* nfa = new NFA(nfa1.startState, nfa2.endState);
    return nfa;
}

NFA* ThomsonConstructor::kleenClosure(NFA nfa) {
    State startState(to_string(id++));
    State endState(to_string(id++));
    nfa.endState.addTransition(epsilon, nfa.startState);
    startState.addTransition(epsilon, nfa.startState);
    nfa.endState.addTransition(epsilon, endState);
    startState.addTransition(epsilon, endState);
    NFA* newNFA = new NFA(startState, endState);
    return newNFA;
}

NFA* ThomsonConstructor::positiveClosure(const NFA& nfa) {
    return concat(nfa, *kleenClosure(nfa));
}

NFA *ThomsonConstructor::getCombinedNFA(vector<pair<string, NFA *>> nfas) {
    State startState(to_string(id++));
    for (const pair<string, NFA*>& pair : nfas) {
        string tokenClass = pair.first;
        NFA* nfa = pair.second;
        startState.addTransition(epsilon, nfa->startState);
        nfa->endState.setIsAccepting(true);
        nfa->endState.setTokenClass(tokenClass);
    }
    NFA* combinedNFA = new NFA(startState);
    return combinedNFA;
}

NFA *ThomsonConstructor::createNFA(vector<char> &inputs) {
    State startState(to_string(id++));
    State endState(to_string(id++));
    startState.addTransitions(inputs, endState);
    NFA* nfa = new NFA(startState, endState);
    return nfa;
}
