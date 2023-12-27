//
// Created by louay on 12/23/23.
//

#ifndef COMPILER_LEFTRECURSIONELIMINATOR_H
#define COMPILER_LEFTRECURSIONELIMINATOR_H

#include <bits/stdc++.h>
#include "NTSorter.h"
using namespace std;

class LeftRecursionEliminator {
    private:
        map<string, vector<vector<string>>> myRules;
        NTSorter nTSorter;
        unordered_set<string> fixedNTs;


        vector<string> sortNonTerminals();
        vector<vector<string>> substituteRule(vector<string> rule);
        vector<vector<string>> substituteRules(const vector<vector<string>>& rules);
        void removeLeftRecursion(const vector<vector<string>>& rulesPerNT, const string& NT);

        static bool areRuleChanged(vector<vector<string>> oldRules, vector<vector<string>> newRules);

    public:
        LeftRecursionEliminator(const map<string, vector<vector<string>>>& rules);
        map<string, vector<vector<string>>> removeLeftRecursion();
};


#endif //COMPILER_LEFTRECURSIONELIMINATOR_H
