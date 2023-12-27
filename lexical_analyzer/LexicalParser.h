//
// Created by louay on 12/4/23.
//

#ifndef COMPILER_LEXICALPARSER_H
#define COMPILER_LEXICALPARSER_H


#include "DFA.h"
#include <bits/stdc++.h>
using namespace std;

class LexicalParser {
private:
    DFA miniDFA;
    DFA* lastAC;
    DFA dFAIterator;

    ifstream sourceProgFile;
    ofstream parsedTokenFile;

    int lastStartDiff;
    long lastStartLine;
    long lastStartCol;
    long lineDiff;
    long colDiff;

    string panicRecover();
    string traverseDFA(char input);

    void closeFile();
    void updateLnColDiff(char input);

public:
    vector<string> tokens;
    bool isClosedFile();

    LexicalParser(const DFA &miniDFA, const string &srcPrgPath);
    ~LexicalParser();

    string getNextToken();

    void writeAllTokens(const string &outFileName);
};

#endif //COMPILER_LEXICALPARSER_H
