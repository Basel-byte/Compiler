//
// Created by Dell on 08/12/2023.
//

#include <algorithm>
#include <fstream>
#include <iostream>
#include <iomanip>
#include "TransitionTableWriter.h"
#include "DFAMinimization.h"

using namespace std;

void TransitionTableWriter::writeTableInTabularForm(set<DFA *> &dfa, string dirpath, string rulesFileName) {
    vector<DFA*> sortedDfa(dfa.begin(), dfa.end());
    sort(sortedDfa.begin(), sortedDfa.end(), DFAMinimization::compareDFAId);
    set<char> inputs = getInputs(sortedDfa);

    ofstream tablefile(dirpath + "/" + rulesFileName + "_transition_table.txt");

    if (!tablefile.is_open()) {
        std::cerr << "Error opening output file!" << std::endl;
        exit(1); // Return an error code
    }

    for (size_t i = 0; i <= inputs.size(); ++i) {
        tablefile << "+=======";
    }
    tablefile << "+" << endl;

    tablefile << setw(4) << "| State";
    for (char input : inputs) {
        tablefile << " | " << setw(3) << input << "  ";
    }
    tablefile << " |" << endl;

    for (size_t i = 0; i <= inputs.size(); ++i) {
        tablefile << "+=======";
    }
    tablefile << "+" << endl;

    set<DFA*> acceptingStates;
    int width = 4;
    for (auto & it : sortedDfa) {
        int id = it->getMinimizationId();
        auto transitions = it->getTransitions();
        tablefile << "|" << setw(4) << id;
        for (char input : inputs) {
            if (transitions.find(input) != transitions.end()) {
                auto next = transitions[input];
                if (next->isAcceptingState()) {
                    acceptingStates.insert(next);
                    tablefile << setw(width) << "|" << setw(width) << "*" + to_string(next->getMinimizationId());
                }
                else
                    tablefile << setw(width) << "|" << setw(width) << next->getMinimizationId();
            }
            else
                tablefile << setw(width) << "|" << setw(width + 1) << "φ";
        }
        tablefile << setw(width) << "|" << endl;

        tablefile << "+-------";
        for (size_t i = 0; i < inputs.size(); ++i) {
            tablefile << "+-------";
        }
        tablefile << "+" << endl;
    }
    tablefile.close();
    writeAcceptingStates(acceptingStates, dirpath, rulesFileName);
}

void TransitionTableWriter::writeAcceptingStates(set<DFA*> &acceptingStates, string dirpath, string rulesFileName) {
    vector<DFA*> sortedStates(acceptingStates.begin(), acceptingStates.end());
    sort(sortedStates.begin(), sortedStates.end(), DFAMinimization::compareDFAId);
    ofstream tablefile(dirpath + "/" + rulesFileName + "_accepting_states.txt");

    tablefile << "+=======+============+" << endl;
    tablefile << setw(4) << "| State";
    tablefile << setw(6) << " | TokenClass";
    tablefile << " |" << endl;
    tablefile << "+=======+============+" << endl;
    for (auto & it : sortedStates) {
        tablefile << "|" << setw(4) << it->getMinimizationId();
        tablefile << setw(4) << "|" << setw(9) << it->getTokenClass();
        tablefile << setw(4) << "|" << endl;
        tablefile << "+-------+------------+" << endl;
    }
    tablefile.close();
};

set<char> TransitionTableWriter::getInputs(vector<DFA *> &dfa) {
    set<char> inputs;
    for (auto it : dfa)
        for (const auto &pair: it->getTransitions())
            inputs.insert(pair.first);
    return inputs;
}