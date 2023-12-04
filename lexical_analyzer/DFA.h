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

    virtual ~DFA();

    DFA(const string &id, int minimizationID);

    DFA(const string &id, bool isAccepting, const string &tokenClass);

    std::string getID() const { return id; }

    DFA* move(char input);

    map<char, DFA*> getTransitions();

    void addTransition(char input, DFA* state);

    bool isAcceptingState() const;

    void setIsAccepting(bool isAccept);

    const string &getTokenClass() const;

    void setTokenClass(const string &ClassToken);

private:
    string id;
    int minimizationID;
    map<char, DFA*> transitions;
    bool isAccepting{};
    string tokenClass;
};



#endif //COMPILER_DFA_H