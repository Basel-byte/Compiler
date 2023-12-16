//
// Created by Dell on 30/11/2023.
//

#include "PriorityTable.h"

int PriorityTable::counter = 1;
map<string, int> PriorityTable::table;

void PriorityTable::addTokenClass(const string& tokenClass) {
    PriorityTable::table[tokenClass] = PriorityTable::counter++;
}

void PriorityTable::addTokenClass(const string& tokenClass, int priority) {
    PriorityTable::table[tokenClass] = priority;
}