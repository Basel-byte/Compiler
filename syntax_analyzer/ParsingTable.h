//
// Created by mai on 12/22/23.
//

#ifndef LEXICALANALYZER_PARSINGTABLE_H
#define LEXICALANALYZER_PARSINGTABLE_H

using namespace std;

#include "map"
#include "vector"
#include "set"


class ParsingTable {
public:
    static map<string, map<string, vector<string>>> getParsingTable(map<string, vector<vector<string>>> rules, map<string, set<string> > firstSet,
                    map<string, set<string> > followSet);
};


#endif //LEXICALANALYZER_PARSINGTABLE_H
