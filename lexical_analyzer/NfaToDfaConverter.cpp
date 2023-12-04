//
// Created by mai on 12/1/23.
//

#include <algorithm>
#include "list"
#include "set"
#include "stack"

using namespace std;
#include "NfaToDfaConverter.h"
#include "DFA.h"
#include <climits>
#include <iostream>

bool compareID(State a, State b) {
    return a.getID() < b.getID();
}

vector<State> NfaToDfaConverter::getEpsilonClosure(State state){
    map<string, int> visited;
    vector<State> epsilons;

    vector<State> toProcess;
    toProcess.push_back(state);
    visited[state.getID()]++;

    epsilons.push_back(state);

    while (!toProcess.empty()) {
        State current = toProcess.back();
        toProcess.pop_back();

        vector<State> epsilonTransitions = current.getTransitions()['\0'];

        for (State &s : epsilonTransitions) {
            if (visited[s.getID()] == 0) {
                visited[s.getID()]++;
                toProcess.push_back(s);
                epsilons.push_back(s);
            }
        }
    }

    // Sort for naming
    sort(epsilons.begin(), epsilons.end(), compareID);

    return epsilons;
}

string NfaToDfaConverter::getStateNewName(vector<State> states) {
    string newName;
    map<string, int> dup;
    // remove duplicate states if occurred
    for (int i = 0; i < states.size(); i++) {
        dup[states[i].getID()]++;
        if(dup[states[i].getID()] > 1){
            states.erase(states.begin() + i);
        }
    }

    for(int i=0; i<states.size(); i++){
        newName += states[i].getID();
        newName += i!=states.size() - 1? "," : "";
    }
    return newName;
}

void NfaToDfaConverter::setAcceptingState(DFA* &dfaState, vector<State>& nfaStates) {
    int maxPriority = INT_MAX;
    string acceptPattern;

    for(const auto & nfaState : nfaStates){
        if(nfaState.isAcceptingState()){
            if(PriorityTable::table[nfaState.getTokenClass()] < maxPriority){
                maxPriority = PriorityTable::table[nfaState.getTokenClass()];
                acceptPattern = nfaState.getTokenClass();
            }
        }

    }

    if(!acceptPattern.empty()){
        dfaState->setIsAccepting(true);
        dfaState->setTokenClass(acceptPattern);
    }
}

vector<DFA> NfaToDfaConverter::convertNFAToDFA(State& startState) {

    // get the epsilon closure of the start state
    vector<State> epsilons = NfaToDfaConverter::getEpsilonClosure(startState);

    // make a new state containing the closure state
    string newName = NfaToDfaConverter::getStateNewName(epsilons);
    DFA inputState(newName); // pointer to the closure state

    map<string, DFA> visitedStates; // visited states
    map<string, pair<DFA, vector<State>>> toProcess; // states to be visited
    toProcess.insert({inputState.getID(), pair<DFA, vector<State>>(inputState, epsilons)});

    // final NfaToDfaConverter state vector
    vector<DFA> dfaStates;

    while (!toProcess.empty()) {
        pair<DFA, vector<State>> temp = toProcess.begin()->second;
        DFA dfaState = temp.first;
        vector<State> nfaStateEpsilons = temp.second;
        toProcess.erase(toProcess.begin());
        dfaStates.push_back(dfaState);
        visitedStates.insert(pair<string, DFA>(dfaState.getID(), dfaState));

        // check if it will be an accept state, if accept state --> set its class token
        NfaToDfaConverter::setAcceptingState(reinterpret_cast<DFA *&>(dfaState), nfaStateEpsilons);

        map<char, vector<State>> currStateTransitions;

        // loop over every epsilon state combined this dfa state to get its reachable states
        for (auto& nfaState : nfaStateEpsilons) {

            map<char, vector<State>> nfaTransitions = nfaState.getTransitions();

            // loop over each input
            for (const auto& inputTransition : nfaTransitions) {
                char in = inputTransition.first;

                if(in != '\0') {
                    vector<State> transitions = inputTransition.second;
                    // loop over each transaction of that specific input
                    for (auto &transition: transitions) {
                        vector<State> eps = NfaToDfaConverter::getEpsilonClosure(transition);

                        if (currStateTransitions[in].empty()) {
                            currStateTransitions[in] = eps;
                        } else {
                            currStateTransitions[in].insert(currStateTransitions[in].end(), eps.begin(), eps.end());
                        }
                    }
                }
            }
        }

        // make new states of the epsilons
        for (auto& itr: currStateTransitions) {

            if (visitedStates.count(NfaToDfaConverter::getStateNewName(itr.second)) != 0 ) { // visited before
                dfaStates.back().addTransition(itr.first, visitedStates.at(NfaToDfaConverter::getStateNewName(itr.second)));
            } else if (toProcess.count(NfaToDfaConverter::getStateNewName(itr.second)) != 0) {
                dfaStates.back().addTransition(itr.first, toProcess.at(NfaToDfaConverter::getStateNewName(itr.second)).first);
            } else {
                DFA newTran(NfaToDfaConverter::getStateNewName(itr.second));
                toProcess.insert({newTran.getID(), pair<DFA, vector<State>>(newTran, itr.second)});
                dfaStates.back().addTransition(itr.first, newTran);
            }
        }

    }

    return dfaStates;
}


