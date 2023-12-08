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
    std::string rulesFilePath, programFilePath, tokensFilePath, outputDirPath;

    // Get the rules file path from the user
    std::cout << "Enter the path of the rules file: \n";
    std::cin >> rulesFilePath;

    // Get the program file path from the user
    std::cout << "Enter the path of the program file: \n";
    std::cin >> programFilePath;

    // Set the tokens file path to be in the same directory as rules file
    tokensFilePath = rulesFilePath.substr(0, programFilePath.find_last_of("/\\") + 1) + "output/tokens.txt";

    // Set the tokens file path to be in the same directory as rules file
    outputDirPath = programFilePath.substr(0, rulesFilePath.find_last_of("/\\") + 1) + "output";

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

    TransitionTableWriter::writeTableInTabularForm(minimizedDfa, outputDirPath);

    DFA* startDFA = DFAMinimization::getStartState(minimizedDfa);

    LexicalParser parser(*startDFA, programFilePath);
    while (!parser.isClosedFile()) {
        std::cout << "Token: " << parser.getNextToken() << std::endl;
    }

    std::cout << "===================================================================\n";
    LexicalParser parserFW(*startDFA, programFilePath);
    parserFW.writeAllTokens(tokensFilePath);
}