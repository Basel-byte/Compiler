//
// Created by louay on 12/23/23.
//

// references:
// 1. Robert C. Moore's general algorithm, https://en.wikipedia.org/wiki/Left_recursion#Removing_left_recursion

#include "LeftRecursionEliminator.h"
using namespace std;

LeftRecursionEliminator ::LeftRecursionEliminator(const map<string, vector<vector<string>>>& rules){
    myRules = rules;
    nTSorter = NTSorter(rules);
}

map<string, vector<vector<string>>> LeftRecursionEliminator :: removeLeftRecursion(){
    vector<string> sortedNT = sortNonTerminals();
    cout << "\nThe Ordering of Non-Terminals before Applying Left Recursion Elimination: \n=> ";
    for(const string& s : sortedNT) cout << s << " ";
    cout << endl;
    for(const string& nT : sortedNT) {
        /// substitute in the NT Productions till no longer substitution required.
        while(true) {
            // for each production A --> B α where B --> β and B rules has no left recursion, let A --> β α
            vector<vector<string>> oldRules = myRules[nT];
            vector<vector<string>> newRules = substituteRules(oldRules);
            if(!areRuleChanged(oldRules, newRules)) break;
            myRules[nT] = newRules;
        }
        fixedNTs.insert(nT); // we can insert the current NT to avoid self substitution
        /// remove left recursion from newRules
        removeLeftRecursion(myRules[nT], nT);
    }
    fixedNTs.clear();
    return myRules;
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

vector<vector<string>> LeftRecursionEliminator :: substituteRules(const vector<vector<string>>& rulesPerNT){
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


void LeftRecursionEliminator :: removeLeftRecursion(const vector<vector<string>>& rulesPerNT, const string& NT){
    vector<vector<string>> recursiveRules;
    vector<vector<string>> independentRules;
    string newNT = NT + "\'";
    for(vector<string> rulePerNT : rulesPerNT){ // Classifying rules to recursive and independent rules
        if(rulePerNT[0] == NT) {
            rulePerNT.erase(rulePerNT.begin());
            rulePerNT.push_back(newNT);
            recursiveRules.push_back(rulePerNT);
        }
        else independentRules.push_back(rulePerNT);
    }
    if(recursiveRules.empty()) return; // no recursive rules, rules are OK in the hash map !!
    recursiveRules.push_back({"\\L"});
    for(vector<string>& independentRule : independentRules) independentRule.push_back(newNT);
    myRules[NT] = independentRules;
    myRules[newNT] = recursiveRules;
}

bool LeftRecursionEliminator :: areRuleChanged(vector<vector<string>> oldRules, vector<vector<string>> newRules){
    if (oldRules.size() != newRules.size()) return true;
    for (size_t i = 0; i < oldRules.size(); ++i) {
        if (oldRules[i].size() != newRules[i].size()) return true;
        for (size_t j = 0; j < oldRules[i].size(); ++j)
            if (oldRules[i][j] != newRules[i][j]) return true;
    }
    return false;
}

