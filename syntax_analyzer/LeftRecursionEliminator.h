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

        vector<string> sortNonTerminals();

    public:
        LeftRecursionEliminator(map<std::string, vector<vector<std::string>>> rules,
                                NTSorter nTSorter);
        map<string, vector<string>> removeLeftRecursion();
};


#endif //COMPILER_LEFTRECURSIONELIMINATOR_H
