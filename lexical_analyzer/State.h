//
// Created by Dell on 30/11/2023.
//

#ifndef COMPILER_STATE_H
#define COMPILER_STATE_H


#include "map"
#include "vector"
using namespace std;

class State {
public:
    State();

    State(bool isAccepting);

    State(bool isAccepting, const string &tokenClass);

    virtual ~State();

    vector<State> move(char input);

    void addTransition(char input, const State& state);

    bool isAcceptingState() const;

    void setIsAccepting(bool isAccepting);

    const string &getTokenClass() const;

    void setTokenClass(const string &tokenClass);

private:
    map<char, vector<State>> transitions;

    bool isAccepting;

    string tokenClass;
};


#endif //COMPILER_STATE_H