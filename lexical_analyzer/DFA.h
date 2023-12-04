//
// Created by mai on 12/3/23.
//

#ifndef COMPILER_DFA_H
#define COMPILER_DFA_H
#include <utility>

#include "map"
#include "vector"
using namespace std;

class DFA {
public:
    DFA();

    DFA(string  name) : id(std::move(name)) {}

    std::string getID() const { return id; }

    virtual ~DFA();

    DFA(bool isAccepting);

    DFA(bool isAccepting, string tokenClass);

    DFA move(char input);


    map<char, DFA> getTransitions();

    void addTransition(char input, const DFA& state);

    bool isAcceptingState() const;

    void setIsAccepting(bool isAccept);

    const string &getTokenClass() const;

    void setTokenClass(const string &ClassToken);

private:
    string id;
    map<char, DFA> transitions;
    bool isAccepting{};
    string tokenClass;
};



#endif //COMPILER_DFA_H
