//
// Created by mai on 12/3/23.
//

#include "DFA.h"

DFA::DFA() {
    isAccepting = false;
    tokenClass = "";
}

DFA::~DFA() = default;


DFA::DFA(const string &id) {
    this->id = id;
    isAccepting = false;
    tokenClass = "";
}

DFA::DFA(const string &id, bool isAccepting, const string &tokenClass) : id(id), isAccepting(isAccepting),
                                                                         tokenClass(tokenClass) {}

DFA* DFA::move(char input) {
    return transitions[input];
}

bool DFA::isAcceptingState() const {
    return isAccepting;
}

void DFA::setIsAccepting(bool isAccept) {
    DFA::isAccepting = isAccept;
}

const string &DFA::getTokenClass() const {
    return tokenClass;
}

void DFA::setTokenClass(const string &ClassToken) {
    DFA::tokenClass = ClassToken;
}

void DFA::addTransition(char input, DFA* state) {
    transitions[input] = state;
}

map<char, DFA*> DFA::getTransitions() {
    return transitions;
}

