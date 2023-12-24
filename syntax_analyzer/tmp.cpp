//
// Created by Dell on 19/12/2023.
//
#include <iostream>
#include <map>
#include <set>
#include <vector>

#include "FollowSet.cpp"
#include "FirstSet.h"

#include <fstream>
#include <iostream>
#include "FirstSet.cpp"
#include "ParsingTable.cpp"

void printTable(map<string, vector<vector<string>>> rules, map<string, map<string, vector<string>>> parsingTable){
    cout<<"\n\n******Parsing Table******\n\n";
    set<string> terminals;
    for(auto rule : rules){
        for(auto term : rule.second) {
            for (auto subTerm: term) {
                if (subTerm[0] == '\'') {
                    terminals.insert(subTerm.substr(1, subTerm.size() - 2));
                }
            }
        }
    }
    terminals.insert("$");
    cout<< "|  NT  |";
    for(auto terminal : terminals){
        cout << "|  " + terminal + "  |";
    }
    cout << "" << endl;
    cout << "------------------------------------------------------------------------" << endl;
    for(auto rule : rules){
        cout<< "|   " + rule.first + "  |";
        for(auto terminal : terminals){
            if(parsingTable[rule.first].find(terminal) != parsingTable[rule.first].end()){
                cout << "|  ";
                for(auto subTerm : parsingTable[rule.first][terminal]){
                    cout<<subTerm;
                }
                cout<<"  |";
            }else{
                cout<<"|  ---  |";
            }
        }
        cout << endl << "==================================================================================================" << endl;
    }
}

int main() {

    // Example grammar
    /* map<string, vector<vector<string>>> rules = {
            {"S", {{"A", "B"}}},
            {"A", {{"'a'", "A"}, {"\\L"}}},
            {"B", {{"'b'", "B"}, {"'c'"}}}
    };*/
    map<string, vector<vector<string>>> rules = {
            {"E", {{"T", "E'"}}},
            {"E'", {{"'+'", "T","E'"}, {"\\L"}}},
            {"T", {{"F", "T'"}}},
            {"T'",{{"'*'","F","T'"},{"\\L"}}},
            {"F", {{"'('", "E","')'"},{"'id'"}}}
    };

    // Print production rules
    for (const auto& rule : rules) {
        std::cout << rule.first << " -> ";
        for (const auto& production : rule.second) {

            for (const auto& symbol : production) {
                std::cout << symbol << " ";
            }
            std::cout << " | ";
        }
        std::cout << std::endl;
    }

    // Compute FIRST sets
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
    string startSymbol ="E";
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
}
