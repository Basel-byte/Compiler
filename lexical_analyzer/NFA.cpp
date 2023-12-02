//
// Created by Dell on 30/11/2023.
//

#include "NFA.h"

NFA::NFA() = default;

NFA::~NFA() = default;

NFA::NFA(const State &startState) : startState(startState) {}

NFA::NFA(const State &startState, const State &endState) : startState(startState), endState(endState) {}

NFA::NFA(const NFA &other) : NFA(other.startState, other.endState) {}

void NFA::setAcceptingState(const string& tokenClass) {
    endState.setIsAccepting(true);
    endState.setTokenClass(tokenClass);
}

