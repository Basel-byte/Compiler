//
// Created by basel on 12/28/23.
//

#ifndef COMPILER_PRINTER_H
#define COMPILER_PRINTER_H

#include <string>
#include <vector>
#include <map>
#include <set>

using namespace std;
class Printer {
public:
    static void printCFG(const string &startSymbol, map<string, vector<vector<string>>> &rules);
    static void printTable(const map<string, map<string, vector<string>>> &parsingTable);
    static void printSet(const map<string, set<string>> &set, const string &s);
    static void printOutput(const vector<pair<bool, string>>& derivations);
};


#endif //COMPILER_PRINTER_H
