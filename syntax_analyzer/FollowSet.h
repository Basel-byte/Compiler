//
// Created by Habiba on 12/23/2023.
//

#ifndef COMPILER_TEST_H
#define COMPILER_FOLLOWSET_H


using namespace std;
#include "map"
#include "vector"
#include "set"

class FollowSet {
public:
    static map<string,set<string>> followSet(map<string, vector<vector<string>>> rules,map<string, set<string>> firstSet , string startSymbol);
};

#endif //COMPILER_TEST_H
