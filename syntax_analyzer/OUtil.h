//
// Created by basel on 12/28/23.
//

#ifndef COMPILER_OUTIL_H
#define COMPILER_OUTIL_H

#include <string>
#include <vector>
#include <map>
#include <set>

using namespace std;
class OUtil {
public:
    static void printCFG(const string &startSymbol, map<string, vector<vector<string>>> &rules);
    static void printTable(const map<string, map<string, vector<string>>> &parsingTable);
    static void printSet(const map<string, set<string>> &set, const string &s);
    static void printOutput(const vector<pair<bool, string>>& output);
    static void writeDerivations(const vector<string> &derivations, const string &dirpath, const string &programFileName);
};


#endif //COMPILER_OUTIL_H
