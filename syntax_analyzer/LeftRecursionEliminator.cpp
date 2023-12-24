//
// Created by louay on 12/23/23.
//

#include "LeftRecursionEliminator.h"
using namespace std;

LeftRecursionEliminator ::LeftRecursionEliminator(map<std::string, vector<vector<std::string>>> rules,
                                                  NTSorter nTSorter) : nTSorter(nTSorter) {
    myRules = rules;
}
map<string, vector<string>> LeftRecursionEliminator :: removeLeftRecursion(){
    vector<string> sortedNT = sortNonTerminals();
    for(const string& s: sortedNT) cout << s << endl;
    map<string, vector<string>> r;
    return r;
}

vector<string> LeftRecursionEliminator :: sortNonTerminals(){
    nTSorter.applyFloydWarshall();
    return nTSorter.getNTSorted();
}
