//
// Created by Dell on 30/11/2023.
//

#include "NFA.h"

NFA::NFA() = default;

NFA::~NFA() = default;

NFA::NFA(const State &startState, const State &endState) : startState(startState), endState(endState) {}

NFA::NFA(int id, const State &startState, const State &endState) : id(id), startState(startState), endState(endState) {}
