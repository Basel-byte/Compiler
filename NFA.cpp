//
// Created by Dell on 30/11/2023.
//

#include "NFA.h"

NFA::NFA() = default;

NFA::~NFA() = default;

vector<int> NFA::move(const int state, const char input) {
    return vector<int>();
}

bool NFA::isAcceptingState(int state) {
    return false;
}

int NFA::getStartState() const {
    return start_state;
}
