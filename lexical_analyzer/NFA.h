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

    NFA(const State &startState, const State &endState);


public:
    State startState;

    State endState;
};


#endif //COMPILER_NFA_H
