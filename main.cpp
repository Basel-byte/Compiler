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

#include "syntax_analyzer/CFGReader.cpp"
#include "syntax_analyzer/NTSorter.cpp"
#include "syntax_analyzer/LeftRecursionEliminator.cpp"
#include "syntax_analyzer/ParsingTable.cpp"
#include "syntax_analyzer/FollowSet.cpp"
#include "syntax_analyzer/FirstSet.cpp"

using namespace std;

string getFileName(const string& filePath) {
    return filePath.substr(filePath.find_last_of("/\\") + 1);
}
void printTable(map<string, vector<vector<string>>> rules, map<string, map<string, vector<string>>> parsingTable){
    cout<<"\n\n******Parsing Table******\n\n";
    cout << "------------------------------------------------------------------------\n" << endl;
    for(auto rule : rules){
        cout<< "****** " + rule.first + " ******\n\n";
        for(auto firstSet : parsingTable[rule.first]){
            cout<< "[ " + firstSet.first + " ] ==> ";
            for(auto first : firstSet.second){
                cout<< first;
            }
            cout<<"\n";
        }
        cout << endl << "==================================================================================================" << endl;
    }
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
    cout<<"jii "<<rulesFileName;
    TransitionTableWriter::writeTableInTabularForm(minimizedDfa, "/home/mai/Compiler/lexical_analyzer/output", rulesFileName);

    DFA* startDFA = DFAMinimization::getStartState(minimizedDfa);
    cout << "===================================================\n";

    /// Parser Part
    cout << "\n\nRules After Left Recursion Elimination: \n";
    CFGReader reader = CFGReader((string &) argv[2]);
    map<string, vector<vector<string>>> rules = reader.parseRules();
    LeftRecursionEliminator lREliminator = LeftRecursionEliminator(rules);
    rules = lREliminator.removeLeftRecursion();
    string startSymbol = reader.getStartSymbol();
    cout << "\nStart Symbol: " << startSymbol << endl;
    for(const auto& pair : rules){
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

    map<string, set<string>> firstSet = FirstSet::firstSet(rules);

    // Print FIRST sets
    cout << "FIRST sets:" << endl;
    for (const auto& entry : firstSet) {
        int count = 0;
        cout << "First( " <<entry.first << " ) = { " ;
        for (const auto& terminal : entry.second) {
            cout << terminal ;
            count++;
            if(count == entry.second.size())
                cout << " }" << endl;
            else
                cout << ", ";
        }

    }


    // Compute FOLLOW sets
    //string startSymbol ="E";
    map<string, set<string>> followSet = FollowSet::followSet(rules, firstSet, startSymbol);



    // Print FOLLOW sets
    cout << "\nFOLLOW sets:" << endl;
    for (const auto& entry : followSet) {
        int count = 0;
        cout << "FOLLOW( " <<entry.first << " ) = { " ;
        for (const auto& terminal : entry.second) {
            cout << terminal ;
            count++;
            if(count == entry.second.size())
                cout << " }" << endl;
            else
                cout << ", ";
        }

    }

    // Print Parsing table
    map<string, map<string, vector<string>>> parsingTable = ParsingTable::getParsingTable(rules, firstSet, followSet);
    printTable(rules, parsingTable);

    return 0;
}

