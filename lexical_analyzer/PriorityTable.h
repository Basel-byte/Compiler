//
// Created by Dell on 30/11/2023.
//

#ifndef COMPILER_PRIORITYTABLE_H
#define COMPILER_PRIORITYTABLE_H

#include "map"
using namespace std;

class PriorityTable {
public:
    static int counter = 0;
    static map<string, int> table;
    void addTokenClass(string tokenClass) {
        table[tokenClass] = counter++;
    }
};


#endif //COMPILER_PRIORITYTABLE_H
