//
// Created by mai on 12/22/23.
//

#include <iostream>
#include "ParsingTable.h"

/*
1. Fill Columns with First set of Non terminals
2. If First (Non-terminal) contains ɛ, look for Follow set.
3. If multiple entries appears in any column, then we can conclude that the given grammar is not LL1.
4. If First (Non-terminal) doesn't contain ɛ but its follow set is not empty, make all follow set values "sync"
 */

set<string> getTermFirst(map<string, vector<vector<string>>> rules, map<string, set<string>> firstSet, vector<string> term){
    int i = 0;
    set<string> subFirst;
    string subTerm = term[i];
    if(subTerm[0] == '\''){
        subFirst.insert(subTerm.substr(1, subTerm.size() - 2));
    }else if(subTerm == "\\L"){
        subFirst.insert(subTerm);
    }else{
        set<string> firstNT = firstSet[subTerm];
        subFirst.insert(firstNT.begin(), firstNT.end());

        for( i = 1; i < term.size(); i++){
            if(subFirst.find("\\L") == subFirst.end()){
                break;
            }else{
                subFirst.erase("\\L");
                subTerm = term[i];
                if(subTerm[0] == '\''){
                    subFirst.insert(subTerm.substr(1, subTerm.size() - 2));
                }else{
                    firstNT = firstSet[subTerm];
                    subFirst.insert(firstNT.begin(), firstNT.end());
                }

            }
        }

    }

    return subFirst;
}


map<string, map<string, vector < string>>> ParsingTable::getParsingTable(map<string, vector<vector<string>>> rules,
map<string, set<string>> firstSet, map<string, set <string>> followSet){

    map<string, map<string, vector < string>>> parsingTable;

    for(const auto& rule : rules){
        map<string, vector<string>> terminalMap;
        for(const auto& term : rule.second){
            set<string> termFirst = getTermFirst(rules, firstSet,term);

            for(const auto& terminal : termFirst){
                if(terminal != "\\L"){
                    if(terminalMap.find(terminal) == terminalMap.end()){
                        terminalMap[terminal] = term;
                    }else{
                        cout << "It's not LL(1) grammar!!" << endl;
                        exit(0);
                    }
                }else{
                   for(const auto& followTerminal : followSet[rule.first]){
                       if(terminalMap.find(followTerminal) == terminalMap.end()){
                           terminalMap[followTerminal] = term;
                       }else{
                           // more than one term (sub Rule) goes to epsilon
                           cout << "It's not LL(1) grammar!!" << endl;
                           exit(0);
                       }
                   }
                }
            }

        }

        // no epsilons
        if(firstSet[rule.first].find("\\L") == firstSet[rule.first].end()){
            for(const auto& followTerminal : followSet[rule.first]){
                if(terminalMap.find(followTerminal) == terminalMap.end()){
                    terminalMap[followTerminal] = {"sync"};
                }
            }
        }

        parsingTable[rule.first] = terminalMap;

    }

    return parsingTable;

}