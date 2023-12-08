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

string getFileName(const string& filePath) {
    return filePath.substr(filePath.find_last_of("/\\") + 1);
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        cerr << "Expected 3 arguments, but got " << argc << std::endl;
        exit(1); // Return an error
    }
    string rulesFilePath = argv[1];

    string rulesFileName = getFileName(rulesFilePath);


    auto start = chrono::high_resolution_clock::now();
    RegexParser regexParser;
    NFA* nfa = regexParser.parseREs(rulesFilePath);
    vector<DFA*> dfa = NfaToDfaConverter::convertNFAToDFA(nfa->startState);
    std::set<DFA*> minimizedDfa = DFAMinimization::minimization(dfa);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);

    cout << "No of NFA states: " << nfa->getSize() << endl;
    cout << "No of DFA states: " << dfa.size() << endl;
    cout << "No of minimized DFA states: " << minimizedDfa.size() << endl;
    cout << "Execution time of grammar parsing: " << duration.count() << " milliseconds" << endl;

    TransitionTableWriter::writeTableInTabularForm(minimizedDfa, "../output", rulesFileName);

    DFA* startDFA = DFAMinimization::getStartState(minimizedDfa);

    for (int i = 2; i < argc; i++) {
        LexicalParser parser(*startDFA, argv[i]);
        while (!parser.isClosedFile()) {
            std::cout << "Token: " << parser.getNextToken() << std::endl;
        }
        std::cout << "===================================================================\n";
        LexicalParser parserFW(*startDFA, argv[i]);
        parserFW.writeAllTokens("../output/" + getFileName(argv[i]) + "_tokens.txt");
    }
}