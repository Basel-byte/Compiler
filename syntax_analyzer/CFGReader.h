//
// Created by louay on 12/23/23.
//

#ifndef COMPILER_CFGREADER_H
#define COMPILER_CFGREADER_H

#include <bits/stdc++.h>
using namespace std;

class CFGReader {
    private:
        ifstream CFGFile;
        string startSymbol;

        static vector<vector<string>> productionToVector(string& production);
        static vector<string> splitOn(string toSplit, const string& separator);
        static string adjustWhiteSpaces(const string& toAdjust);

    public:
        CFGReader(const string& CFGFilePath);
        map<string, vector<vector<string>>> parseRules();
        string getStartSymbol();
};


#endif //COMPILER_CFGREADER_H
