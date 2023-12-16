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

bool compareID(State *a, State *b) {
    return stoi(a->getID()) < stoi(b->getID());
}

vector<State*> NfaToDfaConverter::getEpsilonClosure(State* state){
    set<string> visitedStates;
    stack<State *> states;
    vector<State*> result;

    states.push(state);
    visitedStates.insert(state->getID());
    result.push_back(state);

    while (!states.empty()) {
        State *temp = states.top();
        states.pop();
        vector<State*> closureStates=temp->getTransitions()['\0'];

        for (State* s : closureStates) {

            if (visitedStates.find(s->getID()) == visitedStates.end()) {
                visitedStates.insert(s->getID());
                states.push(s);
                result.push_back(s);
            }

        }
    }
    sort(result.begin(),result.end(),compareID);
    return result;
}

string NfaToDfaConverter::getStateNewName(vector<State*> states) {
    string newName;

    for(int i=0; i<states.size(); i++){
        newName += states[i]->getID();
        newName += i!=states.size() - 1? "," : "";
    }

    return newName;
}

void NfaToDfaConverter::setAcceptingState(DFA* dfaState, const vector<State*>& nfaStates) {
    int maxPriority = INT_MAX;
    string acceptPattern;

    for (auto itr: nfaStates) {
        if (itr->isAcceptingState()) {
            int tempPriority = PriorityTable::table[itr->getTokenClass()] ;
            if (tempPriority < maxPriority) {
                maxPriority = tempPriority;
                acceptPattern = itr->getTokenClass();
            }
        }
    }

    if(!acceptPattern.empty()){
        dfaState->setIsAccepting(true);
        dfaState->setTokenClass(acceptPattern);
    }
}

vector<DFA*> NfaToDfaConverter::convertNFAToDFA(State* startState) {

    int id = 0;
    // get the epsilon closure of the start state
    vector<State*> epsilons = NfaToDfaConverter::getEpsilonClosure(startState);

    // make a new state containing the closure state
    string newName = NfaToDfaConverter::getStateNewName(epsilons);
    DFA* inputState = new DFA(newName, id); // pointer to the closure state
    id++;

    map<string, DFA*> visitedStates; // visited states
    map<string, pair<DFA*, vector<State*>>> toProcess; // states to be visited
    toProcess.insert({inputState->getID(), pair<DFA*, vector<State*>>(inputState, epsilons)});

    // final NfaToDfaConverter state vector
    vector<DFA*> dfaStates;

    while (!toProcess.empty()) {
        pair<DFA*, vector<State*>> temp = toProcess.begin()->second;
        vector<State*> nfaStateEpsilons = temp.second;
        toProcess.erase(toProcess.begin());
        dfaStates.push_back(temp.first);
        visitedStates.insert(pair<string, DFA*>(temp.first->getID(), temp.first));

        // check if it will be an accept state, if accept state --> set its class token
        NfaToDfaConverter::setAcceptingState(temp.first, nfaStateEpsilons);

        map<char, vector<State*>> currStateTransitions;

        // loop over every epsilon state combined this dfa state to get its reachable states
        for (auto nfaState : nfaStateEpsilons) {
            map<char, vector<State*>> nfaTransitions = nfaState->getTransitions();

            // loop over each input
            for ( auto inputTransition : nfaTransitions) {
                char in = inputTransition.first;

                if(in != '\0' && in != ' ') {

                    // loop over each transaction of that specific input
                    for (auto transition: inputTransition.second) {

                        if (currStateTransitions.find(in) == currStateTransitions.end()) {
                            vector<State*> eps = NfaToDfaConverter::getEpsilonClosure(transition);
                            currStateTransitions.insert({in, eps});
                        } else {
                            vector<State*> eps = NfaToDfaConverter::getEpsilonClosure(transition);
                        //    currStateTransitions.at(in).insert(currStateTransitions.at(in).end(),eps.begin(), eps.end());

                            for (auto& state : eps) {
                                // Check if the state already exists in currStateTransitions.at(in)
                                if (find(currStateTransitions.at(in).begin(), currStateTransitions.at(in).end(), state) == currStateTransitions.at(in).end()) {
                                    // State is not found, add it to currStateTransitions.at(in)
                                    currStateTransitions.at(in).push_back(state);
                                }
                            }
                        }
                    }
                }
            }
        }

        // make new states of the epsilons
        for (const auto& itr: currStateTransitions) {

            if (visitedStates.count(NfaToDfaConverter::getStateNewName(itr.second)) != 0 ) { // visited before
                temp.first->addTransition(itr.first, visitedStates.at(NfaToDfaConverter::getStateNewName(itr.second)));
            } else if (toProcess.count(NfaToDfaConverter::getStateNewName(itr.second)) != 0) {
                temp.first->addTransition(itr.first, toProcess.at(NfaToDfaConverter::getStateNewName(itr.second)).first);
            } else {
                DFA* newTran = new DFA(NfaToDfaConverter::getStateNewName(itr.second), id);
                id++;
                toProcess.insert({newTran->getID(), pair<DFA*, vector<State*>>(newTran, itr.second)});
                temp.first->addTransition(itr.first, newTran);
            }
        }

    }

    return dfaStates;
}