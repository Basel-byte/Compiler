//
// Created by Dell on 30/11/2023.
//

#ifndef COMPILER_NFA_H
#define COMPILER_NFA_H


#include "State.h"
#include "map"

class NFA {
public:
    NFA();

    virtual ~NFA();

    NFA(State* startState);

    NFA(State* startState, State* endState);

    NFA(const NFA &other);

    void setAcceptingState(const string& tokenClass) const;

public:
    State *startState;
    State *endState;
};


#endif //COMPILER_NFA_H
