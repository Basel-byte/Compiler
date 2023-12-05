//
// Created by Habiba on 12/4/2023.
//

using namespace std;

#include <vector>
#include <set>
#include <queue>
#include <map>
#include <algorithm>
#include <iostream>
#include "NfaToDfaConverter.h"
#include "DFAMinimization.h"
#include "DFA.h"
#include <climits>

bool compareDFAId(DFA *i1, DFA *i2) {
    return i1->getMinimizationId() < i2->getMinimizationId();
}

set<DFA *> DFAMinimization::minimization(vector<DFA *> dfaStates) {


    // sort the dfa states by their id
    sort(dfaStates.begin(), dfaStates.end(), compareDFAId);

    //2D boolean array to mark distinguishable pairs of states.
    //bool pairsArray[dfaStates.size()][dfaStates.size()] = {{false}};


    // Assuming dfaStates is a vector or another container with a size() method
    std::vector<std::vector<bool>> pairsArray(dfaStates.size(), std::vector<bool>(dfaStates.size(), false));


    //1 - marking distinguishable patterns Distinguishable pairs are marked based on
    // whether they are accepting states and if they have different accepting patterns.



    for (int i = 0; i < dfaStates.size(); i++) {
        DFA *firstState = dfaStates.at(i);

        //iterates over states preceding the current state (i).
        // This avoids unnecessary duplication since pairs are symmetric (i, j) and (j, i) would be the same pair.
        for (int j = 0; j < i; j++) {

            DFA *secondState = dfaStates.at(j);

            // if one is accepting and the other not, so they are different states
            if ((firstState->isAcceptingState() && !secondState->isAcceptingState()) ||
                (!firstState->isAcceptingState() && secondState->isAcceptingState()))
                pairsArray[i][j] = true;

                //if both accepting states check if they have different token class if so, so they are different
            else if (firstState->isAcceptingState() && secondState->isAcceptingState() &&
                     (firstState->getTokenClass() != secondState->getTokenClass()))
                pairsArray[i][j] = true;

        }
    }

    bool findPairs = true;

    // 2-refine the marking of distinguishable pairs by considering the sizes and detailed content of state transition functions.
    // It ensures that the process is iteratively applied until no more pairs can be marked as distinguishable

    while (findPairs) {

        findPairs = false;

        for (int i = 0; i < dfaStates.size(); i++) {

            DFA *firstState = dfaStates.at(i);

            map < char, DFA * > firstStateTransitions = firstState->getTransitions();

            for (int j = 0; j < i; j++) {

                DFA *secondState = dfaStates.at(j);
                map < char, DFA * > secondStateTransitions = secondState->getTransitions();


                if (!pairsArray[i][j]) {// if they are not distinguishable "equivalent"
                    if (firstStateTransitions.size() !=
                        secondStateTransitions.size()) {//if size different so it's different
                        pairsArray[i][j] = true;
                        findPairs = true;

                    } else {// if size equal detailed comparison
                        // we will compare the transition state with each other for same input

                        for (auto itr = firstStateTransitions.begin(); itr != firstStateTransitions.end(); itr++) {
                            char inputSymbol = itr->first;

                            // if that inputSymbol exists in secondState so need to compare the transition states for both
                            if (secondStateTransitions.find(inputSymbol) != secondStateTransitions.end()) {
                                int index1 = itr->second->getMinimizationId(); // get id of  first transition
                                int index2 = secondStateTransitions.find(inputSymbol)->second->getMinimizationId();  // get id of  second transition

                                //because our  loop iterates over states preceding the current state (i).
                                // so i > j
                                int row = max(index1, index2);
                                int col = min(index1, index2);


                                if (pairsArray[row][col]) {
                                    pairsArray[i][j] = true;
                                    findPairs = true;
                                }


                            } else { // if that input doesn't exist in second state so they aren't equivalent
                                pairsArray[i][j] = true;
                                findPairs = true;
                            }
                        }
                    }
                }


            }
        }
    }

    //Each set within minimizedStates corresponds to a group of states that are considered equivalent in the minimized DFA.
    set <set<DFA *>> minimizedStates;


    //to keep track of sets of states that are not yet marked as equivalent.
    queue <set<DFA *>> notMarked;

    //This set is markedAsUsed to keep track of individual states that have been included in sets and marked as "markedAsUsed"
    set < DFA * > markedAsUsed;

    for (int i = 0; i < dfaStates.size(); i++) {
        for (int j = 0; j < i; j++) {
            if (!pairsArray[i][j]) {// means state i  and state j equivalent
                set < DFA * > temp;
                temp.insert(dfaStates.at(i));
                temp.insert(dfaStates.at(j));
                notMarked.push(temp);// push equivalent states to notMarked
                // marking states as markedAsUsed by pushing them in markedAsUsed
                markedAsUsed.insert(dfaStates.at(i));
                markedAsUsed.insert(dfaStates.at(j));
            }
        }
    }

    //any states that have not been marked as "markedAsUsed" are considered as sets with a single state and are added to minimizedStates
    // all states that are not in markedAsUsed (equivalent states) are pushed into minimizationstates
    for (auto itr: dfaStates) {
        if (markedAsUsed.find(itr) ==
            markedAsUsed.end()) {  // state mawgoda fel dfa states w m4 mawgoda fel markedAsUsed
            set < DFA * > temp;
            temp.insert(itr);
            minimizedStates.insert(temp);
        }
    }

    //3- combining equivalent states

    while (!notMarked.empty()) {

        set < DFA * > states = notMarked.front();
        notMarked.pop();

        std::set < DFA * > combinedStates(states);//initializes a new set with the states dequeued
        int size = notMarked.size();
        bool found = false;
        //The loop that follows will attempt to find additional states that are equivalent to those in the combinedStates set.
        for (int i = 0; i < size; i++) {
            set < DFA * > temp = notMarked.front();
            for (auto itr: temp) {
                //Checks if a state in temp is already in combinedStates, indicating that the sets share equivalent states.
                if (combinedStates.find(itr) != combinedStates.end()) {
                    combinedStates.insert(temp.begin(), temp.end());
                    found = true; //Marks that equivalent states were found.
                    break;
                }
            }
            //
            notMarked.pop();
            //if equivalent states were not found, temp is pushed back into the queue.
            if (!found)
                notMarked.push(temp);
            else
                found = false;
        }

        minimizedStates.insert(combinedStates);
    }

    return  DFAMinimization::minimizeHelper(minimizedStates);

}

void DFAMinimization::setAcceptingMinimizedStateDFA(DFA *dfaState, set<DFA *> states) {
    int maxPriority = INT_MAX;
    string acceptPattern;
    for (auto itr: states) {
        if (itr->isAcceptingState()) {
            int tempPriority = PriorityTable::table[itr->getTokenClass()];
            if (tempPriority < maxPriority) {
                maxPriority = tempPriority;

                acceptPattern = itr->getTokenClass();
            }
        }
    }

    //lesa
    if(!acceptPattern.empty()){
        dfaState->setIsAccepting(true);
        dfaState->setTokenClass(acceptPattern);
        //dfaState->patternPriority = maxPriority;
    }

}

string DFAMinimization::minimizedStateName(set<DFA*> states) {
    string name ="";
    for (auto itr: states)
        name.append(itr->getID()); // id is the string field

    return name;
}

set<DFA *> DFAMinimization::minimizeHelper(set<set<DFA *>> minimizedStates) {

    int id=0;
    set<pair<set<DFA*>,DFA*>> combinedStates;
    //iterates over each set in minimizedStates
    // to create new combined states and associate them with a unique name.
    for (auto itr : minimizedStates)
    {
        //  it creates a new Dfa State (newState) with a unique index (id) and a name obtained using minimizedStateName
        DFA* newState=new DFA(minimizedStateName(itr), id);

        // determines whether the new state is an accepting state
        DFAMinimization::setAcceptingMinimizedStateDFA(newState, itr);

        combinedStates.insert({itr,newState});
        id++;
    }


    set<DFA*> result;
    for (auto combinedState : combinedStates) {
        DFA * startState = *(combinedState.first.begin());
        map<char, DFA *> mainTransitions = startState->getTransitions();

        for (auto itr: mainTransitions) { // itr (input ,destination)
            for (auto loopState: combinedStates) { //  Each pair represents (a set of original DFA states , a new combined state).
                if (loopState.first.find(itr.second) != loopState.first.end()) {
                    combinedState.second->addTransition(itr.first,loopState.second);
                    break;
                }
            }
        }
        result.insert(combinedState.second);
    }

    return result;
}





