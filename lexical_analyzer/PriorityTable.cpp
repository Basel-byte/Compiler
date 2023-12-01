//
// Created by Dell on 30/11/2023.
//

#include "PriorityTable.h"

int PriorityTable::counter = 0;

void PriorityTable::addTokenClass(const string& tokenClass) {
    PriorityTable::table[tokenClass] = PriorityTable::counter++;
}