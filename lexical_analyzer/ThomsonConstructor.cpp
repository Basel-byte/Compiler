//
// Created by Dell on 01/12/2023.
//

#include "ThomsonConstructor.h"

char ThomsonConstructor::epsilon = '\0';

NFA* ThomsonConstructor::creatBasic(char input) {
    auto *startState = new State();
    auto *endState = new State();
    startState->addTransition(input, endState);
    NFA* nfa = new NFA(startState, endState);
    return nfa;
}

NFA* ThomsonConstructor::createEpsilon() {
    return creatBasic(epsilon);
}

NFA* ThomsonConstructor::range(char src, char dest) {
    auto *startState = new State();
    auto *endState = new State();
    for (int i = int(src); i <= int(dest); i++)
        startState->addTransition((char)i, endState);
    NFA* nfa = new NFA(startState, endState);
    return nfa;
}

NFA* ThomsonConstructor::union_(NFA nfa1, NFA nfa2) {
    auto *startState = new State();
    auto *endState = new State();
    startState->addTransition(epsilon, nfa1.startState);
    startState->addTransition(epsilon, nfa2.startState);
    nfa1.endState->addTransition(epsilon, endState);
    nfa2.endState->addTransition(epsilon, endState);
    NFA* nfa = new NFA(startState, endState);
    return nfa;
}

NFA* ThomsonConstructor::concat(NFA nfa1, const NFA& nfa2) {
    nfa1.endState->addTransition(epsilon, nfa2.startState);
    NFA* nfa = new NFA(nfa1.startState, nfa2.endState);
    return nfa;
}

NFA* ThomsonConstructor::kleenClosure(NFA nfa) {
    auto *startState = new State();
    auto *endState = new State();
    nfa.endState->addTransition(epsilon, nfa.startState);
    startState->addTransition(epsilon, nfa.startState);
    nfa.endState->addTransition(epsilon, endState);
    startState->addTransition(epsilon, endState);
    NFA* newNFA = new NFA(startState, endState);
    return newNFA;
}

NFA* ThomsonConstructor::positiveClosure(const NFA& nfa) {
    return concat(nfa, *kleenClosure(nfa));
}

NFA *ThomsonConstructor::getCombinedNFA(const vector<pair<string, NFA *>>& nfas) {
    auto *startState = new State();
    for (const pair<string, NFA*>& pair : nfas) {
        string tokenClass = pair.first;
        NFA* nfa = pair.second;
        startState->addTransition(epsilon, nfa->startState);
        nfa->endState->setIsAccepting(true);
        nfa->endState->setTokenClass(tokenClass);
    }
    NFA* combinedNFA = new NFA(startState);
    combinedNFA->giveIDs();
    return combinedNFA;
}

NFA *ThomsonConstructor::createNFA(vector<char> &inputs) {
    auto *startState = new State();
    auto *endState = new State();
    startState->addTransitions(inputs, endState);
    NFA* nfa = new NFA(startState, endState);
    return nfa;
}
