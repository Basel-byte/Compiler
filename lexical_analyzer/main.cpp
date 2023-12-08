//
// Created by Dell on 03/12/2023.
//

#include <iostream>
#include <chrono>
#include "NFA.h"
#include "RegexParser.h"
#include "State.h"
#include "PriorityTable.h"
#include "DFA.h"
#include "NfaToDfaConverter.h"
#include "LexicalParser.h"
#include "DFAMinimization.h"
#include "TransitionTableWriter.h"

using namespace std;

int main() {
    auto start = chrono::high_resolution_clock::now();
    RegexParser regexParser;
    NFA* nfa = regexParser.parseREs("../SampleTests/rules/rules1");
    vector<DFA*> dfa = NfaToDfaConverter::convertNFAToDFA(nfa->startState);
    std::set<DFA*> minimizedDfa = DFAMinimization::minimization(dfa);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);

    cout << "No of NFA states: " << nfa->getSize() << endl;
    cout << "No of DFA states: " << dfa.size() << endl;
    cout << "No of minimized DFA states: " << minimizedDfa.size() << endl;
    cout << "Execution time of grammar parsing: " << duration.count() << " milliseconds" << endl;

    TransitionTableWriter::writeTableInTabularForm(minimizedDfa, "../SampleTests/output");

    DFA* startDFA = DFAMinimization::getStartState(minimizedDfa);
    LexicalParser parser(*startDFA, "../SampleTests/testPrograms/program1.txt");
    while(!parser.isClosedFile()) cout << "Token: " << parser.getNextToken() << endl;
    cout << "===================================================================\n";
    LexicalParser parserFW(*startDFA, "../SampleTests/testPrograms/program1.txt");
    parserFW.writeAllTokens("../SampleTests/output/tokens.txt");

}