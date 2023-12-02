//
// Created by mai on 12/1/23.
//


#include <iostream>
#include <algorithm>
using namespace std;
#include "DFA.h"
#include <climits>

bool compareID(State *a, State *b) {
    return a->getID() < b->getID();
}

vector<State*> DFA::getEpsilonClosure(State* state){
    map<State*, int> visited;
    vector<State*> epsilons;

    vector<State*> toProcess;
    toProcess.push_back(state);
    visited[state]++;

    epsilons.push_back(state);

    while (!toProcess.empty()) {
        State* current = toProcess.back();
        toProcess.pop_back();

        vector<State> epsilonTransitions = current->getTransitions()['\0'];

        for (State &s : epsilonTransitions) {
            if (visited[&s] == 0) {
                visited[&s]++;
                toProcess.push_back(&s);
                epsilons.push_back(&s);
            }
        }
    }

    // Sort for naming
    sort(epsilons.begin(), epsilons.end(), compareID);

    return epsilons;
}

string DFA::getStateNewName(vector<State*> states) {
    string newName;
    map<string, int> dup;

    // remove duplicate states if occurred
    for (int i = 0; i < states.size(); i++) {
        dup[states[i]->getID()]++;
        if(dup[states[i]->getID()] > 1){
            states.erase(states.begin() + i);
        }
    }
    for(int i=0; i<states.size(); i++){
        newName += states[i]->getID();
        newName += i!=states.size() ? "," : "";
    }

    return newName;
}

void DFA::setAcceptingState(State* dfaState, const vector<State*>& nfaStates) {
    int maxPriority = INT_MAX;
    string acceptPattern;

    for(const auto & nfaState : nfaStates){
        if(nfaState->isAcceptingState()){
            if(PriorityTable::table[nfaState->getTokenClass()] < maxPriority){
                maxPriority = PriorityTable::table[nfaState->getTokenClass()];
                acceptPattern = nfaState->getTokenClass();
            }
        }

    }

    if(!acceptPattern.empty()){
        dfaState->setIsAccepting(true);
        dfaState->setTokenClass(acceptPattern);
    }
}

vector<State*> DFA::convertNFAToDFA(State startNFAState) {

    State* startState = &startNFAState;

    // get the epsilon closure of the start state
    vector<State*> epsilons = DFA::getEpsilonClosure(startState);

    // make a new state containing the closure state
    State input = new State(DFA::getStateNewName(epsilons));
    State* inputState = &input; // pointer to the closure state

    map<string, State*> visitedStates; // visited states
    map<string, pair<State*, vector<State*>>> toProcess; // states to be visited
    toProcess.insert({inputState->getID(), pair<State*, vector<State*>>(inputState, epsilons)});

    // final DFA state vector
    vector<State*> dfaStates;

    while (!toProcess.empty()) {
        pair<State*, vector<State*>> temp = toProcess.begin()->second;
        State* dfaState = temp.first;
        vector<State*> nfaStateEpsilons = temp.second;
        toProcess.erase(toProcess.begin());
        dfaStates.push_back(dfaState);
        visitedStates.insert(pair<string, State*>(dfaState->getID(), dfaState));

        // check if it will be an accept state, if accept state --> set its class token
        DFA::setAcceptingState(dfaState, nfaStateEpsilons);

        map<char, vector<State*>> currStateTransitions;

        // loop over every epsilon state combined this dfa state to get its reachable states
        for (auto& nfaState : nfaStateEpsilons) {

            map<char, vector<State>> nfaTransitions = nfaState->getTransitions();

            // loop over each input
            for (const auto& inputTransition : nfaTransitions) {
                char in = inputTransition.first;
                vector<State> transitions = inputTransition.second;
                // loop over each transaction of that specific input
                for (auto & transition : transitions) {
                    const State* constTrans = &transition;
                    vector<State*> eps = DFA::getEpsilonClosure(const_cast<State*>(constTrans));
                    if (currStateTransitions[in].empty()) {
                        currStateTransitions[in] = eps;
                    }else {
                        currStateTransitions[in].insert(currStateTransitions[in].end(), eps.begin(), eps.end());
                    }
                }
            }
        }

        // make new states of the epsilons
        for (const auto& itr: currStateTransitions) {
            if (visitedStates.count(DFA::getStateNewName(itr.second)) != 0 ) { // visited before
                dfaState->addTransition(itr.first, visitedStates.at(DFA::getStateNewName(itr.second)));
            } else if (toProcess.count(DFA::getStateNewName(itr.second)) != 0) {
                dfaState->addTransition(itr.first, toProcess.at(DFA::getStateNewName(itr.second)).first);
            } else {
                auto* newTran = new State(DFA::getStateNewName(itr.second));
                toProcess.insert({newTran->getID(), pair<State*, vector<State*>>(newTran, itr.second)});
                dfaState->addTransition(itr.first, newTran);
            }
        }
    }

    return dfaStates;
}


