//
// Created by Dell on 19/12/2023.
//
#include <iostream>
#include <map>
#include <set>
#include <vector>

#include "FollowSet.h"
#include "FirstSet.h"

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
    FirstSet firstSetCalculator;
    map<string, set<string>> firstSets = firstSetCalculator.firstSet(rules);

    // Print FIRST sets
    cout << "FIRST sets:" << endl;
    for (const auto& entry : firstSets) {
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
    FollowSet followSetCal;
    string startSymbol ="E";
    map<string, set<string>> followSet = followSetCal.followSet(rules, firstSets, startSymbol);



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


    return 0;
}
