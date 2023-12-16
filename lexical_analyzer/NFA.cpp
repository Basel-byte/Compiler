//
// Created by Dell on 30/11/2023.
//

#include <iostream>
#include "NFA.h"
#include "set"

NFA::NFA() = default;

NFA::~NFA() = default;

NFA::NFA(State* startState) : startState(startState) {}

NFA::NFA(State *startState, State *endState) : startState(startState), endState(endState) {}

NFA::NFA(const NFA &other) {
    endState = new State(*(other.endState));
    map<State*, State*> map;
    map[other.endState] = endState;
    startState = new State(*(other.startState), map);
}

void NFA::setAcceptingState(const string& tokenClass) const {
    endState->setIsAccepting(true);
    endState->setTokenClass(tokenClass);
}

int NFA::getSize() const {
    return size + 1;
}

void NFA::giveIDs() {
    size = 0;
    set<State*> visited;
    startState->setIDs(&size, visited);
}
string NFA::toString() const {
    return startState->toString();
}
