//
// Created by Dell on 30/11/2023.
//

#include "NFA.h"

NFA::NFA() = default;

NFA::~NFA() = default;

NFA::NFA(State* startState) : startState(startState) {}

NFA::NFA(State *startState, State *endState) : startState(startState), endState(endState) {}

NFA::NFA(const NFA &other) {
    endState = new State(*(other.endState));
    map<string, State*> map;
    map[endState->getID()] = endState;
    startState = new State(*(other.startState), map);
}

void NFA::setAcceptingState(const string& tokenClass) const {
    endState->setIsAccepting(true);
    endState->setTokenClass(tokenClass);
}