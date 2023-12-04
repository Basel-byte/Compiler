//
// Created by Dell on 03/12/2023.
//

#include <iostream>
#include "ThomsonConstructor.h"
#include "NFA.h"
#include "RegexParser.h"
#include "State.h"
#include "Utility.h"
#include "PriorityTable.h"
#include "DFA.h"
#include "NfaToDfaConverter.h"

int main() {

//    RegexParser regexParser;
//    NFA* nfa = regexParser.parseREs("D:/Computer and Systems Engineering/7th Semster\\Compilers/Project/Compiler/lexical_analyzer/rules");
//    return 0;

    NFA* part1 = ThomsonConstructor::range('a', 'c');
    NFA* part2 = ThomsonConstructor::kleenClosure(*part1);
    NFA* part3 = ThomsonConstructor::creatBasic('a');
    NFA* part4 = ThomsonConstructor::concat(*part2, *part3);

    NFA* part5 = ThomsonConstructor::range('a', 'c');
    State* end1 = &part5->endState;
    end1->setIsAccepting(true);
    end1->setTokenClass("T1");
    NFA* part6 = ThomsonConstructor::kleenClosure(*part5);
    NFA* part7 = ThomsonConstructor::concat(*part4, *part6);

    NFA* part8 = ThomsonConstructor::range('a', 'c');
    NFA* part9 = ThomsonConstructor::kleenClosure(*part8);
    NFA* part10 = ThomsonConstructor::createEpsilon();
    NFA* part11 = ThomsonConstructor::creatBasic('b');
    NFA* part12 = ThomsonConstructor::creatBasic('c');
    State* end2 = &part12->endState;
    end2->setIsAccepting(true);
    end2->setTokenClass("T2");
    NFA* part13 = ThomsonConstructor::concat(*part11, *part12);
    NFA* part14 = ThomsonConstructor::positiveClosure(*part13);
    NFA* part15 = ThomsonConstructor::concat(*part9, *part10);
    NFA* part16 = ThomsonConstructor::concat(*part15, *part14);

    cout << part7->endState.isAcceptingState();
    NFA* part17 = ThomsonConstructor::union_(*part7, *part16);

    PriorityTable::addTokenClass("T1");
    PriorityTable::addTokenClass("T2");

    std::cout << "Debug: ID = \"" << part17->startState.getTransitions()['\0'][0].getTransitions()['\0'][1].getTransitions().size() << "\"" << std::endl;

    vector<DFA> dfa = NfaToDfaConverter::convertNFAToDFA(part17->startState);
   // cout<<"----------------------------------------------------------------------------------";
    cout<<dfa.size()<<"\n";
    for (int i = 0; i < dfa.size(); i++) {
        for (auto& pair : dfa[i].getTransitions()) {
            cout <<  dfa[i].getID() <<" ---" << pair.first << "---> "<< pair.second.getID()<<"\n";
        }
        cout<<"----------------------------------------------------------------------------------\n";
    }
}
