//
// Created by Dell on 30/11/2023.
//

#ifndef COMPILER_NFA_H
#define COMPILER_NFA_H

#include "map"
#include "vector"
using namespace std;

class NFA {
public:
    NFA();
    virtual ~NFA();
    vector<int> move(int state, char input);
    bool isAcceptingState(int state);
    int getStartState() const;
private:
    int start_state;
    map<int, int> priority;
    map<int, map<char, vector<int>>> nfa;
    map<int, string> accepting_states;
};


#endif //COMPILER_NFA_H
