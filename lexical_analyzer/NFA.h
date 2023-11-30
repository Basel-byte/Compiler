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
    int getPriority(const string& tokenClass);
    string getTokenClass(int acceptingState);
private:
    int startState;
    map<string, int> priority;  // tokenClass -> priority
    map<int, map<char, vector<int>>> nfa;  // state --input--> vector of states
    map<int, string> acceptingStates;  // state -> tokenClass
};


#endif //COMPILER_NFA_H
