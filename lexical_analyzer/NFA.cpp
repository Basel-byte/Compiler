//
// Created by Dell on 30/11/2023.
//

#include "NFA.h"

NFA::NFA() = default;

NFA::~NFA() = default;

vector<int> NFA::move(const int state, const char input) {
    return nfa[state][input];
}

bool NFA::isAcceptingState(int state) {
    return acceptingStates.find(state) != acceptingStates.end();
}

int NFA::getStartState() const {
    return startState;
}
