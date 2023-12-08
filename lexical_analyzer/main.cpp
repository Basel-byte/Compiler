//
// Created by Dell on 03/12/2023.
//

#include <iostream>
#include "ThomsonConstructor.h"
#include "NFA.h"
#include "RegexParser.h"
#include "State.h"
#include "PriorityTable.h"
#include "DFA.h"
#include "NfaToDfaConverter.h"
#include "LexicalParser.h"
#include "DFAMinimization.h"
using namespace std;

int main() {

    RegexParser regexParser;
    NFA* nfa = regexParser.parseREs("/home/louay/Compiler/lexical_analyzer/SampleTests/rules/rules1");
    cout << nfa->getSize() << " nfa states" << endl;
    vector<DFA*> dfa = NfaToDfaConverter::convertNFAToDFA(nfa->startState);


    cout<<dfa.size()<<"\n T1 --> red,  T2 --> green, nt acceptance state --> blue\n";
    for (size_t i = 0; i < dfa.size(); ++i) {
        for (const auto &pair: dfa[i]->getTransitions()) {
            // Print the ID and transition information
            std::cout << (dfa[i]->isAcceptingState() ? (dfa[i]->getTokenClass() == "T1" ? "\033[1;31m" : "\033[1;32m")
                                                     : "\033[1;34m")
                      << dfa[i]->getID() << " ---" << pair.first << "---> "
                      << (pair.second->isAcceptingState() ? (pair.second->getTokenClass() == "T1" ? "\033[1;31m"
                                                                                                  : "\033[1;32m")
                                                          : "\033[1;34m")
                      << pair.second->getID() << " " << pair.second->getTokenClass() << "\033[0m\n";
        }
        cout << "--------------------------------------------------------------------------------\n";
    }

    std::set<DFA*> minimizedDfa = DFAMinimization::minimization(dfa);
    DFA* startDFA;
    int i=0;
    for (auto it = minimizedDfa.begin(); it != minimizedDfa.end(); ++it) {
        if((*it)->getMinimizationId()==0){
            startDFA = (*it);
        }
        i++;
        for (const auto &pair: (*it)->getTransitions()) {
            // Print the ID and transition information
            std::cout<< (*it)->getMinimizationId() << " ---" << pair.first << "---> "
                     << pair.second->getMinimizationId() << " " << pair.second->getTokenClass() << "\n";

        }
        std::cout << "--------------------------------------------------------------------------------\n";
    }

    std::ofstream outFile("/home/louay/Compiler/lexical_analyzer/SampleTests/output/minimizedDFA.txt");

    if (!outFile.is_open()) {
        std::cerr << "Error opening output file!" << std::endl;
        return 1; // Return an error code
    }


    for (auto it = minimizedDfa.begin(); it != minimizedDfa.end(); ++it) {

        for (const auto &pair: (*it)->getTransitions()) {
            outFile << (*it)->getMinimizationId() << " ---" << pair.first << "---> "
                    << pair.second->getMinimizationId() << " " << pair.second->getTokenClass() << "\n";

        }
        if ((*it)->getTransitions().empty()) {
            outFile << (*it)->getMinimizationId() << " final acceptance state ( " << (*it)->getTokenClass() << " )\n";
        }
        outFile << "--------------------------------------------------------------------------------\n";
    }

    outFile.close();

    LexicalParser parser(*startDFA, "/home/louay/Compiler/lexical_analyzer/SampleTests/testPrograms/program1.txt");
    while(!parser.isClosedFile()) cout << "Token: " << parser.getNextToken() << endl;
    cout << "===================================================================\n";
    LexicalParser parserFW(*startDFA, "/home/louay/Compiler/lexical_analyzer/SampleTests/testPrograms/program1.txt");
    parserFW.writeAllTokens("/home/louay/Compiler/lexical_analyzer/SampleTests/output/tokens.txt");

}