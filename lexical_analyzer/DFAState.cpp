//
// Created by mai on 12/3/23.
//

#include "DFAState.h"
#include <utility>

DFAState::DFAState(string id) : id(std::move(id)) {}

DFAState::DFAState() {
    isAccepting = false;
    tokenClass = nullptr;
}

DFAState::~DFAState() = default;

DFAState::DFAState(bool isAccepting) : isAccepting(isAccepting) {}

DFAState::DFAState(bool isAccepting, string tokenClass) : isAccepting(isAccepting), tokenClass(std::move(tokenClass)) {}

DFAState DFAState::move(char input) {
    return transitions[input];
}

bool DFAState::isAcceptingState() const {
    return isAccepting;
}

void DFAState::setIsAccepting(bool isAccept) {
    DFAState::isAccepting = isAccept;
}

const string &DFAState::getTokenClass() const {
    return tokenClass;
}

void DFAState::setTokenClass(const string &ClassToken) {
    DFAState::tokenClass = ClassToken;
}

void DFAState::addTransition(char input, const DFAState& state) {
    transitions[input] = state;
}

map<char, DFAState> DFAState::getTransitions() {
    return transitions;
}

string DFAState::getID() {
    return id;
}
