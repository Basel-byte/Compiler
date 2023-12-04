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

    State(string id);

    State(bool isAccepting);

    State(bool isAccepting, string tokenClass);

    State(string id, bool isAccepting, string tokenClass);

    State(const State &other, map<string, State*> &map);

    virtual ~State();

    vector<State*> move(char input);

    string getID();

    map<char, vector<State*>> getTransitions();

    void addTransition(char input, State *state);

    void addTransitions(const vector<char>& inputs, State* state);

    void addTransitions(char input, vector<State*> states);

    bool isAcceptingState() const;

    void setIsAccepting(bool isAccepting);

    const string &getTokenClass() const;

    void setTokenClass(const string &tokenClass);

    void set(string id, bool isAccepting, string tokenClass);

private:
    string id;
    map<char, vector<State*>> transitions;
    bool isAccepting{};
    string tokenClass;
};


#endif //COMPILER_STATE_H