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
    vector<pair<char, NFA *>> tokenize(string rhs, map<int, string> &posToMatch);
    void parseLine(string line);
    void parseRE(const string& lhs, string rhs);
    void parsePunctuationSymbols(string symbols);
    bool isOperator(char c);
    NFA *getCombinedNFA();
    void findNonOverlappingMatches(const string &input, const regex &reg, map<int, string> &posToMatch);
    static void findAllOccurrences(const string& input, const regex& reg, map<int, string> &posToMatch);
    static string escapeRegex(const string& input);
private:
    regex keywordsRegex;
    regex punctRegex;
    regex rangeLetter;
    regex rangeDigit;
    regex epsilonRegex;
    map<string, NFA*> regexMap;
    set<char> operators; // - | + * ( )
};


#endif //COMPILER_REGEXPARSER_H
