//
// Created by Dell on 30/11/2023.
//

#include "State.h"

#include <utility>

State::State() {
    isAccepting = false;
    tokenClass = "";
}

State::State(string id) : id(std::move(id)) {}

State::~State() = default;

State::State(bool isAccepting) : isAccepting(isAccepting) {}

State::State(bool isAccepting, string tokenClass) : isAccepting(isAccepting), tokenClass(std::move(tokenClass)) {}

State::State(string id, bool isAccepting, string tokenClass) : id(std::move(id)), isAccepting(isAccepting),
                                                                             tokenClass(std::move(tokenClass)) {}

State::State(const State &other, map<string, State*> &map) {
    set(other.id, other.isAccepting, other.tokenClass);
    map[id] = this;
    for (const auto& pair : other.transitions) {
        char c = pair.first;
        const auto & vector = pair.second;
        for (const auto& next: vector) {
            if (map.find(next->id) == map.end())
                addTransition(c, new State(*next, map));
            else
                addTransition(c, map[next->id]);
        }
    }
}

vector<State*> State::move(char input) {
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

void State::addTransition(char input, State *state) {
    transitions[input].push_back(state);
}

void State::addTransitions(const vector<char>& inputs, State* state) {
    for (char input : inputs)
        addTransition(input, state);
}

void State::addTransitions(char input, vector<State*> states) {
    transitions[input] = std::move(states);
}

map<char, vector<State*>> State::getTransitions() {
    return transitions;
}

string State::getID() {
    return id;
}

void State::set(string i, bool isAccept, string tc) {
    this->id = std::move(i);
    this->isAccepting = isAccept;
    this->tokenClass = std::move(tc);
}