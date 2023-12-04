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

using namespace std;

int main() {
    RegexParser regexParser;
    NFA* nfa = regexParser.parseREs("D:/Computer and Systems Engineering/7th Semster\\Compilers/Project/Compiler/lexical_analyzer/rules");
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

    DFA *A = new DFA("A", 1), *B = new DFA("B", 2),
    *C = new DFA("C", 3), *D = new DFA("D", 4),
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

    LexicalParser parser(*A, "/home/louay/Compiler/lexical_analyzer/program.txt");
    while(!parser.isClosedFile()) cout << "Token: " << parser.getNextToken() << endl;

    LexicalParser parserFW(*A, "/home/louay/Compiler/lexical_analyzer/program.txt");
    parserFW.writeAllTokens("/home/louay/Compiler/lexical_analyzer/tokens.txt");
}
