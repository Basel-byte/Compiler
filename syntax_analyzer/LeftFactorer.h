//
// Created by basel on 12/26/23.
//

#ifndef COMPILER_LEFTFACTORER_H
#define COMPILER_LEFTFACTORER_H

#include <string>
#include <vector>
#include <map>
#include <set>

using namespace std;

class LeftFactorer {
public:
    static map<string, vector<vector<string>>> leftFactor(map<string, vector<vector<string>>> &rules);
private:
    static vector<pair<string, vector<vector<string>>>>
    leftFactor(pair<string, vector<vector<string>>> productions, set<string> &NTs);
    static void sortProductions(vector<vector<string>> &productions);
    static pair<size_t, pair<size_t, size_t>> getMatches(size_t index, vector<vector<string>> &productions);
    static size_t getMaxMatch(size_t matchSize, size_t i, size_t j, vector<vector<string>> &productions);
    static pair<string, vector<vector<string>>>
    createNewProductions(const string &NT, pair<size_t, pair<int, int>> matches, vector<vector<string>> &productions);
    static string findSymbolToTheNewNT(const string& NT, set<string> &NTs);
    static set<string> getNTs(map<string, vector<vector<string>>> &rules);
};

#endif //COMPILER_LEFTFACTORER_H
