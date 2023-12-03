//
// Created by mai on 12/3/23.
//

#ifndef COMPILER_DFASTATE_H
#define COMPILER_DFASTATE_H
#include "map"
#include "vector"
using namespace std;

class DFAState {
public:
    DFAState();

    DFAState(string id);

    virtual ~DFAState();

    DFAState(bool isAccepting);

    DFAState(bool isAccepting, string tokenClass);

    DFAState move(char input);

    string getID();

    map<char, DFAState> getTransitions();

    void addTransition(char input, const DFAState& state);

    bool isAcceptingState() const;

    void setIsAccepting(bool isAccept);

    const string &getTokenClass() const;

    void setTokenClass(const string &ClassToken);

private:
    string id;
    map<char, DFAState> transitions;
    bool isAccepting{};
    string tokenClass;
};



#endif //COMPILER_DFASTATE_H
