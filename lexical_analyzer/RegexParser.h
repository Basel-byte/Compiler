//
// Created by Dell on 01/12/2023.
//

#ifndef COMPILER_REGEXPARSER_H
#define COMPILER_REGEXPARSER_H

#include "map"
#include "set"
#include "vector"
#include "regex"
#include "NFA.h"

using namespace std;

class RegexParser {
public:
    RegexParser();
    NFA * parseREs(const string& filepath);
private:
    vector<pair<char, NFA *>> tokenize(string rhs, map<int, smatch> posToMatch);
    void parseLine(string line);
    void parseRE(const string& lhs, string rhs);
    void parsePunctuationSymbols(string symbols);
    bool isOperator(char c);
private:
    regex keywordsRegex;
    regex punctRegex;
    regex rangeLetter;
    regex rangeDigit;
    map<string, NFA*> regexMap;
    set<char> operators; // - | + * ( )
    NFA *getCombinedNFA();
};


#endif //COMPILER_REGEXPARSER_H
