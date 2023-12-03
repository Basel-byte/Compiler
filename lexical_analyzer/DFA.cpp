//
// Created by mai on 12/3/23.
//

#include "DFA.h"
#include <utility>

DFA::DFA(string id) : id(std::move(id)) {}

DFA::DFA() {
    isAccepting = false;
    tokenClass = nullptr;
}

DFA::~DFA() = default;

DFA::DFA(bool isAccepting) : isAccepting(isAccepting) {}

DFA::DFA(bool isAccepting, string tokenClass) : isAccepting(isAccepting), tokenClass(std::move(tokenClass)) {}

DFA DFA::move(char input) {
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

void DFA::addTransition(char input, const DFA& state) {
    transitions[input] = state;
}

map<char, DFA> DFA::getTransitions() {
    return transitions;
}

string DFA::getID() {
    return id;
}
