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

    std::string rulesFilePath, programFilePath, tokensFilePath, minimizedDFAPath;

    // Get the rules file path from the user
    std::cout << "Enter the path of the rules file: ";
    std::cin >> rulesFilePath;

    // Get the program file path from the user
    std::cout << "Enter the path of the program file: ";
    std::cin >> programFilePath;

    // Set the tokens file path to be in the same directory as rules file
    tokensFilePath = rulesFilePath.substr(0, rulesFilePath.find_last_of("/\\") + 1) + "output/tokens.txt";

    // Set the tokens file path to be in the same directory as rules file

    minimizedDFAPath = programFilePath.substr(0, rulesFilePath.find_last_of("/\\") + 1) + "output/minimizedDFA.txt";
///home/mai/Compiler/lexical_analyzer/SampleTests/rules/rules1
///home/mai/Compiler/lexical_analyzer/SampleTests/testPrograms/program1.txt
    RegexParser regexParser;
    NFA* nfa = regexParser.parseREs(rulesFilePath);
    std::cout << nfa->getSize() << " nfa states" << std::endl;
//    DFA* dfa = new DFA("1");
//    dfa->addTransition('e', *dfa);
//    NFA* part1 = ThomsonConstructor::range('a', 'c');
//    NFA* part2 = ThomsonConstructor::kleenClosure(*part1);
//    NFA* part3 = ThomsonConstructor::creatBasic('a');
//    NFA* part4 = ThomsonConstructor::concat(*part2, *part3);
//
//    NFA* part5 = ThomsonConstructor::range('a', 'c');
//    State* end1 = part5->endState;
//    end1->setIsAccepting(true);
//    end1->setTokenClass("T1");
//    NFA* part6 = ThomsonConstructor::kleenClosure(*part5);
//    NFA* part7 = ThomsonConstructor::concat(*part4, *part6);
//
//    NFA* part8 = ThomsonConstructor::range('a', 'c');
//    NFA* part9 = ThomsonConstructor::kleenClosure(*part8);
//    NFA* part10 = ThomsonConstructor::createEpsilon();
//    NFA* part11 = ThomsonConstructor::creatBasic('b');
//    NFA* part12 = ThomsonConstructor::creatBasic('c');
//    State* end2 = part12->endState;
//    end2->setIsAccepting(true);
//    end2->setTokenClass("T2");
//    NFA* part13 = ThomsonConstructor::concat(*part11, *part12);
//    NFA* part14 = ThomsonConstructor::positiveClosure(*part13);
//    NFA* part15 = ThomsonConstructor::concat(*part9, *part10);
//    NFA* part16 = ThomsonConstructor::concat(*part15, *part14);
//
//    NFA* part17 = ThomsonConstructor::union_(*part7, *part16);
//
//    PriorityTable::addTokenClass("T1");
//    PriorityTable::addTokenClass("T2");
//
//    std::cout << "Debug: ID = \"" << part17->startState->getTransitions()['\0'][0]->getTransitions()['\0'][1]->getTransitions().size() << "\"" << std::endl;
//
//    vector<DFA*> dfa = NfaToDfaConverter::convertNFAToDFA(part17->startState);
//    NFA* nfa = regexParser.parseREs("/home/louay/Compilers-Project/lexical_analyzer/rules");
    vector<DFA*> dfa = NfaToDfaConverter::convertNFAToDFA(nfa->startState);


    // cout<<"----------------------------------------------------------------------------------";
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
///home/mai/Compiler/lexical_analyzer/SampleTests/testPrograms/program1.txt
    std::ofstream outFile("/home/mai/Compiler/lexical_analyzer/SampleTests/output/minimizedDFA.txt");

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

    LexicalParser parser(*startDFA, programFilePath);
    while (!parser.isClosedFile()) {
        std::cout << "Token: " << parser.getNextToken() << std::endl;
    }

    std::cout << "===================================================================\n";
    LexicalParser parserFW(*startDFA, programFilePath);
    parserFW.writeAllTokens("/home/mai/Compiler/lexical_analyzer/SampleTests/output/tokens.txt");



//    NFA* part1 = ThomsonConstructor::creatBasic('b');
//    NFA* part2 = ThomsonConstructor::creatBasic('a');
//    State* end1 = part2->endState;
//    NFA* part3 = ThomsonConstructor::concat(*part1, *part2);
//
//    NFA* part4 = ThomsonConstructor::creatBasic('b');
//    NFA* part5 = ThomsonConstructor::creatBasic('a');
//    NFA* part6 = ThomsonConstructor::concat(*part4, *part5);
//    NFA* part7 = ThomsonConstructor::creatBasic('b');
//    NFA* part8 = ThomsonConstructor::concat(*part6, *part7);
//
//    NFA* part9 = ThomsonConstructor::creatBasic('b');
//    NFA* part10 = ThomsonConstructor::creatBasic('b');
//    NFA* part11 = ThomsonConstructor::kleenClosure(*part10);
//    NFA* part12 = ThomsonConstructor::concat(*part9, *part11);
//    NFA* part13 = ThomsonConstructor::creatBasic('a');
//    NFA* part14 = ThomsonConstructor::kleenClosure(*part13);
//    NFA* part15 = ThomsonConstructor::concat(*part12, *part14);
//
//    pair<string, NFA*> p1;
//    p1.first = "P1"; p1.second = part3;
//    pair<string, NFA*> p2;
//    p2.first = "P2"; p2.second = part8;
//    pair<string, NFA*> p3;
//    p3.first = "P3"; p3.second = part15;
//    vector<pair<string, NFA*>> combinedNFA;
//    combinedNFA.push_back(p1);
//    combinedNFA.push_back(p2);
//    combinedNFA.push_back(p3);
//    NFA* part16 = ThomsonConstructor::getCombinedNFA(combinedNFA);

    /*   RegexParser regexParser;
       NFA* nfa = regexParser.parseREs("D:/Computer and Systems Engineering/7th Semster\\Compilers/Project/Compiler/lexical_analyzer/rules2");
   //    DFA *dfa = new DFA("1");
   //    dfa->addTransition('e', *dfa);
       NFA* part1 = ThomsonConstructor::range('a', 'c');
       NFA* part2 = ThomsonConstructor::kleenClosure(*part1);
       NFA* part3 = ThomsonConstructor::creatBasic('a');
       NFA* part4 = ThomsonConstructor::concat(*part2, *part3);

       NFA* part5 = ThomsonConstructor::range('a', 'c');
       State* end1 = part5->endState;
       end1->setIsAccepting(true);
       end1->setTokenClass("T1");
       NFA* part6 = ThomsonConstructor::kleenClosure(*part5);
       NFA* part7 = ThomsonConstructor::concat(*part4, *part6);

       NFA* part8 = ThomsonConstructor::range('a', 'c');
       NFA* part9 = ThomsonConstructor::kleenClosure(*part8);
       NFA* part10 = ThomsonConstructor::createEpsilon();
       NFA* part11 = ThomsonConstructor::creatBasic('b');
       NFA* part12 = ThomsonConstructor::creatBasic('c');
       State* end2 = part12->endState;
       end2->setIsAccepting(true);
       end2->setTokenClass("T2");
       NFA* part13 = ThomsonConstructor::concat(*part11, *part12);
       NFA* part14 = ThomsonConstructor::positiveClosure(*part13);
       NFA* part15 = ThomsonConstructor::concat(*part9, *part10);
       NFA* part16 = ThomsonConstructor::concat(*part15, *part14);

       NFA* part17 = ThomsonConstructor::union_(*part7, *part16);

       PriorityTable::addTokenClass("T1");
       PriorityTable::addTokenClass("T2");

       std::cout << "Debug: ID = \"" << part17->startState->getTransitions()['\0'][0]->getTransitions()['\0'][1]->getTransitions().size() << "\"" << std::endl;

       vector<DFA*> dfa = NfaToDfaConverter::convertNFAToDFA(part17->startState);
      // cout<<"----------------------------------------------------------------------------------";
       cout<<dfa.size()<<"\n T1 --> red,  T2 --> green, nt acceptance state --> blue\n";
       for (size_t i = 0; i < dfa.size(); ++i) {
           for (const auto& pair : dfa[i]->getTransitions()) {
               // Print the ID and transition information
               std::cout << (dfa[i]->isAcceptingState()? (dfa[i]->getTokenClass()=="T1"? "\033[1;31m" : "\033[1;32m" ): "\033[1;34m")
                         << dfa[i]->getID() << " ---" << pair.first << "---> "
                         << (pair.second->isAcceptingState()? (pair.second->getTokenClass()=="T1"? "\033[1;31m" : "\033[1;32m" ): "\033[1;34m")
                         << pair.second->getID() << "\033[0m\n";
           }
           cout<<"--------------------------------------------------------------------------------\n";
       }

       DFA *A = new DFA("A", 0), *B = new DFA("B", 1),
       *C = new DFA("C", 4), *D = new DFA("D", 4),
       *E = new DFA("E", 5), *F = new DFA("F", 6);

       A->setIsAccepting(false);
       B->setIsAccepting(true); B->setTokenClass("b+a*");
       C->setIsAccepting(true); C->setTokenClass("ba");
       D->setIsAccepting(true); D->setTokenClass("b+a*");
       E->setIsAccepting(true); E->setTokenClass("b+a*");
       F->setIsAccepting(true); F->setTokenClass("bab");

       A->addTransition('b', B);
       B->addTransition('a', C); B->addTransition('b', D);
       C->addTransition('a', E); C->addTransition('b', F);
       D->addTransition('a', E); D->addTransition('b', D);
       E->addTransition('a', E);

       LexicalParser parser(*A, "/home/louay/Compiler/lexical_analyzer/program2.txt");
       while(!parser.isClosedFile()) cout << "Token: " << parser.getNextToken() << endl;

       LexicalParser parserFW(*A, "/home/louay/Compiler/lexical_analyzer/program2.txt");
       parserFW.writeAllTokens("/home/louay/Compiler/lexical_analyzer/tokens.txt");*/
}