//
// Created by mai on 12/21/23.
//

#ifndef COMPILER_FIRSTSET_H
#define COMPILER_FIRSTSET_H

using namespace std;
#include "map"
#include "vector"
#include "set"

class FirstSet {
public:
    static map<string,set<string>> firstSet(map<string, vector<vector<string>>> rules);
};


#endif //COMPILER_FIRSTSET_H
