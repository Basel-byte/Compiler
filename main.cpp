//
// Created by Dell on 03/12/2023.
//

#include <iostream>
#include <chrono>
#include "lexical_analyzer/NFA.cpp"
#include "lexical_analyzer/RegexParser.cpp"
#include "lexical_analyzer/State.cpp"
#include "lexical_analyzer/PriorityTable.cpp"
#include "lexical_analyzer/DFA.cpp"
#include "lexical_analyzer/NfaToDfaConverter.cpp"
#include "lexical_analyzer/LexicalParser.cpp"
#include "lexical_analyzer/DFAMinimization.cpp"
#include "lexical_analyzer/TransitionTableWriter.cpp"
#include "lexical_analyzer/ThomsonConstructor.cpp"
#include "lexical_analyzer/Utility.cpp"

#include "syntax_analyzer/CFGReader.h"
#include "syntax_analyzer/NTSorter.h"
#include "syntax_analyzer/LeftRecursionEliminator.h"
#include "syntax_analyzer/LeftFactorer.h"
#include "syntax_analyzer/ParsingTable.h"
#include "syntax_analyzer/FollowSet.h"
#include "syntax_analyzer/FirstSet.h"
#include "syntax_analyzer/SyntaxParser.h"
#include "syntax_analyzer/OUtil.h"

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

    cout << "\n\nLexical Analyzer Output:\n";
    for (int i = 3; i < argc; i++) {
        LexicalParser parser(*startDFA, argv[i]);
        while (!parser.isClosedFile()) {
            string tokenClass = parser.getNextToken();
            std::cout << "Token: ";
            if (tokenClass == "$")
                std::cout << "Input File EOF has been reached!!" << std::endl;
            else
                std::cout << tokenClass << std::endl;
        }
        std::cout << "===================================================================\n";
        LexicalParser parserFW(*startDFA, argv[i]);
        parserFW.writeAllTokens("../lexical_analyzer/output/" + getFileName(argv[i]) + "_tokens.txt");
    }

    /// Parser Part
    CFGReader reader = CFGReader(argv[2]);
    map<string, vector<vector<string>>> rules = reader.parseRules();
    LeftRecursionEliminator lREliminator = LeftRecursionEliminator(rules);
    rules = lREliminator.removeLeftRecursion();
    string startSymbol = reader.getStartSymbol();
    cout << "\n\nRules After Left Recursion Elimination: \n";
    OUtil::printCFG(startSymbol, rules);
    rules = LeftFactorer::leftFactor(rules);
    cout << "\n\nRules After Left Factoring: \n";
    OUtil::printCFG(startSymbol, rules);

    std::cout << "\n===================================================================\n";

    // Compute FIRST sets
    map<string, set<string>> firstSet = FirstSet::firstSet(rules);
    OUtil::printSet(firstSet, "FIRST");

    std::cout << "\n===================================================================\n";

    // Compute FOLLOW sets
    //string startSymbol ="E";
    map<string, set<string>> followSet = FollowSet::followSet(rules, firstSet, startSymbol);
    OUtil::printSet(followSet, "FOLLOW");

    std::cout << "\n===================================================================\n";

    // Print Parsing table
    map<string, map<string, vector<string>>> parsingTable = ParsingTable::getParsingTable(rules, firstSet, followSet);
    OUtil::printTable(parsingTable);

    for (int i = 3; i < argc; i++) {
        LexicalParser lexicalParser(*startDFA, argv[i]);
        SyntaxParser::init(lexicalParser, parsingTable, startSymbol);
        auto pair = SyntaxParser::parseProgram();
        OUtil::writeDerivations(pair.first, "../syntax_analyzer/output", getFileName(argv[i]));
        OUtil::printOutput(pair.second);
        std::cout << "\n===================================================================\n";
    }
    return 0;
}

