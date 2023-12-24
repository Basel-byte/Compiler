//
// Created by Dell on 03/12/2023.
//

#include <iostream>
#include <chrono>
#include "NFA.h"
#include "lexical_analyzer/RegexParser.h"
#include "lexical_analyzer/State.h"
#include "lexical_analyzer/PriorityTable.h"
#include "lexical_analyzer/DFA.h"
#include "lexical_analyzer/NfaToDfaConverter.h"
#include "lexical_analyzer/LexicalParser.h"
#include "lexical_analyzer/DFAMinimization.h"
#include "lexical_analyzer/TransitionTableWriter.h"

#include "syntax_analyzer/CFGReader.h"
#include "syntax_analyzer/NTSorter.h"
#include "syntax_analyzer/LeftRecursionEliminator.h"

using namespace std;

string getFileName(const string& filePath) {
    return filePath.substr(filePath.find_last_of("/\\") + 1);
}

int main(int argc, char* argv[]) {
    // arguments are as follows:
    // 1. Lexical Rules FilePath
    // 2. CFG Rules FilePath
    // 3. paths of any number of input source programs

    if (argc < 3) {
        cerr << "Expected 4 arguments, but got " << argc << std::endl;
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

    TransitionTableWriter::writeTableInTabularForm(minimizedDfa, "../lexical_analyzer/output", rulesFileName);

    DFA* startDFA = DFAMinimization::getStartState(minimizedDfa);
    cout << "===================================================\n";

    /// Parser Part
    cout << "\n\nRules After Left Recursion Elimination: \n";
    CFGReader reader = CFGReader((string &) argv[2]);
    map<string, vector<vector<string>>> rules = reader.parseRules();
    LeftRecursionEliminator lREliminator = LeftRecursionEliminator(rules);
    rules = lREliminator.removeLeftRecursion();
    for(auto pair : rules){
        cout << "\nNon-Terminal: " << pair.first << endl;
        vector<vector<string>> rulesPerNT = pair.second;
        for (const auto& rule : rulesPerNT) {
            cout << "--> [";
            for (size_t i = 0; i < rule.size(); ++i) {
                cout << rule[i];
                if (i < rule.size() - 1) cout << ", ";
            }
            cout << "]" << endl;
        }
    }
    cout << "===================================================\n";
    cout << "\n\nLexical Analyzer Output:\n";
    for (int i = 3; i < argc; i++) {
        LexicalParser parser(*startDFA, argv[i]);
        while (!parser.isClosedFile()) {
            std::cout << "Token: " << parser.getNextToken() << std::endl;
        }
        std::cout << "===================================================================\n";
        LexicalParser parserFW(*startDFA, argv[i]);
        parserFW.writeAllTokens("../lexical_analyzer/output/" + getFileName(argv[i]) + "_tokens.txt");
    }

    return 0;
}