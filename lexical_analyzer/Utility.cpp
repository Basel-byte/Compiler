//
// Created by Dell on 01/12/2023.
//

#include "Utility.h"
#include "ThomsonConstructor.h"
#include "stack"

NFA* Utility::getCorrespondingNFA(vector<pair<char, NFA*>> infix) {
    vector<pair<char, NFA*>> postfix = infixToPostfix(infix);
    stack<NFA*> st;
    for (pair<char, NFA*> pair : postfix) {
        if (pair.second != nullptr)
            st.push(pair.second);
        else {
            if (isUnary(pair.first)) {
                NFA* nfa = doOperation(pair.first, st.top(), nullptr);
                st.pop();
                st.push(nfa);
            }
            else {
                if (st.size() < 2)
                    break;
                NFA* nfa2 = st.top();
                st.pop();
                NFA* nfa1 = st.top();
                st.pop();
                NFA* nfa = doOperation(pair.first, nfa1, nfa2);
                st.push(nfa);
            }
        }
    }
    return st.size() == 1 ? st.top() : nullptr;;
}

vector<pair<char, NFA *>> Utility::infixToPostfix(const vector<pair<char, NFA*>>& infix) {
    vector<pair<char, NFA*>> postfix;
    stack<char> st;
    for (pair<char, NFA*> pair : infix) {
        char c = pair.first;
        if (pair.second != nullptr)
            postfix.emplace_back(pair);
        else {
            if (c == '(')
                st.push(c);
            else if (c == ')') {
                while (!st.empty() && st.top() != '(') {
                    postfix.emplace_back(st.top(), nullptr);
                    st.pop();
                }
                st.pop();
            }
            else {
                while (!st.empty() && getPrecedence(st.top()) >= getPrecedence(c)) {
                    postfix.emplace_back(st.top(), nullptr);
                    st.pop();
                }
                st.push(c);
            }
        }
    }
    while (!st.empty()) {
        postfix.emplace_back(st.top(), nullptr);
        st.pop();
    }
    return postfix;
}

NFA* Utility::doOperation(char c, NFA* nfa1, NFA* nfa2) {
    switch(c) {
        case '|':
            return ThomsonConstructor::union_(*nfa1, *nfa2);
        case '\1':
            return ThomsonConstructor::concat(*nfa1, *nfa2);
        case '*':
            return ThomsonConstructor::kleenClosure(*nfa1);
        case '+':
            return ThomsonConstructor::positiveClosure(*nfa1);
        default:
            return nullptr;
    }
}

int Utility::getPrecedence(char c) {
    switch (c) {
        case '|':
            return 1;
        case '\1':
            return 2;
        case '*':
            return 3;
        case '+':
            return 3;
        default:
            return -1;
    }
}

bool Utility::isUnary(char c) {
    return c == '*' || c == '+';
}