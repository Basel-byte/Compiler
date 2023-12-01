//
// Created by Dell on 30/11/2023.
//

#ifndef COMPILER_PRIORITYTABLE_H
#define COMPILER_PRIORITYTABLE_H

#include "map"
using namespace std;

class PriorityTable {
public:
    static int counter;
    static map<string, int> table;
    static void addTokenClass(const string& tokenClass);
};

#endif //COMPILER_PRIORITYTABLE_H
