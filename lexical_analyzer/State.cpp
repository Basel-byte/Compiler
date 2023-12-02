//
// Created by Dell on 30/11/2023.
//

#include "State.h"

#include <utility>

State::State() {
    isAccepting = false;
    tokenClass = nullptr;
}

State::State(string id) : id(std::move(id)) {}

State::~State() = default;

State::State(bool isAccepting) : isAccepting(isAccepting) {}

State::State(bool isAccepting, const string &tokenClass) : isAccepting(isAccepting), tokenClass(tokenClass) {}

vector<State> State::move(char input) {
    return transitions[input];
}

bool State::isAcceptingState() const {
    return isAccepting;
}

void State::setIsAccepting(bool isAccepting) {
    State::isAccepting = isAccepting;
}

const string &State::getTokenClass() const {
    return tokenClass;
}

void State::setTokenClass(const string &tokenClass) {
    State::tokenClass = tokenClass;
}

void State::addTransition(char input, const State& state) {
    transitions[input].push_back(state);
}

map<char, vector<State>> State::getTransitions() {
    return transitions;
}

string State::getID() {
    return id;
}
