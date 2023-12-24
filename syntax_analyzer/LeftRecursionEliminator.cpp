//
// Created by louay on 12/23/23.
//

#include "LeftRecursionEliminator.h"
using namespace std;

LeftRecursionEliminator ::LeftRecursionEliminator(map<string, vector<vector<string>>> rules){
    myRules = rules;
    nTSorter = NTSorter(rules);
}

map<string, vector<string>> LeftRecursionEliminator :: removeLeftRecursion(){
    vector<string> sortedNT = sortNonTerminals();

    for(const string& nT : sortedNT){
        // Substitute with old encountered NT
        cout << nT << endl;
        vector<vector<string>> oldRules = myRules[nT];
        vector<vector<string>> newRules = substituteRules(oldRules);

        for(vector<string> r : newRules){
            std::cout << "[";
            for (size_t i = 0; i < r.size(); ++i) {
                std::cout << r[i];
                if (i < r.size() - 1) {
                    std::cout << ", ";
                }
            }
            std::cout << "]" << std::endl;
        }

        fixedNTs.insert(nT); // we can insert the current NT to avoid self substitution
        /// remove left recursion from newRules
        /// insert fixed rule into myRules[nT]
    }



    map<string, vector<string>> r;
    return r;
}

vector<string> LeftRecursionEliminator :: sortNonTerminals(){
    nTSorter.applyFloydWarshall();
    return nTSorter.getNTSorted();
}

vector<vector<string>> LeftRecursionEliminator :: substituteRule(vector<string> rulePerNT){
    string toSubstitute = rulePerNT.front();
    rulePerNT.erase(rulePerNT.begin());

    vector<vector<string>> rulesToSubsWith = myRules[toSubstitute];
    vector<vector<string>> result;
    for(const vector<string>& r : rulesToSubsWith){
        result.push_back(r);
        for (const string& tOrNT : rulePerNT) result.back().push_back(tOrNT);
    }
    return result;
}

vector<vector<string>> LeftRecursionEliminator :: substituteRules(vector<vector<string>> rulesPerNT){
    vector<vector<string>> newRules;
    for(const vector<string>& rule : rulesPerNT) { // substitution step
        if(fixedNTs.find(rule[0]) != fixedNTs.end()) { // an encountered Non-Terminal
            vector<vector<string>> subsRules = substituteRule(rule);
            for(const vector<string>& subsRule : subsRules) newRules.push_back(subsRule);
        }
        else newRules.push_back(rule);
    }
    return newRules;
}


void LeftRecursionEliminator :: removeLeftRecursion(vector<vector<string>> rulesPerNT, string NT){

}
