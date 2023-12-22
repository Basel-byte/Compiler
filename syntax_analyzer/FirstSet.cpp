//
// Created by mai on 12/21/23.
//

#include <iostream>
#include "FirstSet.h"

/*
If x is a terminal, then FIRST(x) = { ‘x’ }
If x-> Є, is a production rule, then add Є to FIRST(x).
If X->Y1 Y2 Y3….Yn is a production,
  1) FIRST(X) = FIRST(Y1)
  2) If FIRST(Y1) contains Є then FIRST(X) = { FIRST(Y1) – Є } U { FIRST(Y2) }
  3) If FIRST (Yi) contains Є for all i = 1 to n, then add Є to FIRST(X).
 */

map<string,set<string>> firstSetMap;

set<string> getFirst( map<string, vector<vector<string>>>& rules, string nonTerminal){
    if(firstSetMap[nonTerminal].empty()){
        set<string> subFirst;
        for(auto term : rules[nonTerminal]){

            int i = 0;
            string subTerm = term[i];
            if(subTerm[0] == '\''){
               subFirst.insert(subTerm.substr(1, subTerm.size() - 2));
            }else if(subTerm == "\\L"){
               subFirst.insert(subTerm);
            }else{
               set<string> firstNT = getFirst(rules,subTerm);
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
                           firstNT = getFirst(rules,subTerm);
                           subFirst.insert(firstNT.begin(), firstNT.end());
                       }

                   }
               }

            }
        }

        firstSetMap[nonTerminal] = subFirst;
        subFirst.clear();

    }

    return firstSetMap[nonTerminal];
}

map<string,set<string>> FirstSet::firstSet(map<string, vector<vector<string>>> rules){

   for(const auto& rule : rules){
       getFirst(rules, rule.first);
   }

   return firstSetMap;
}

