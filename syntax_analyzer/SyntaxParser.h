//
// Created by basel on 12/27/23.
//

#ifndef COMPILER_SYNTAXPARSER_H
#define COMPILER_SYNTAXPARSER_H

#include <string>
#include <stack>
#include "../lexical_analyzer/LexicalParser.h"

using namespace std;
class SyntaxParser {
public:
    static void init(LexicalParser &lexicalParser,
                                 const map<string, map<string, vector<string>>> &parsingTable,
                                 const string &startSymbol_);

    static pair<vector<string>, vector<pair<bool, string>>> parseProgram();
private:
    static LexicalParser* lexicalParser;
    static map<string, map<string, vector<string>>> parsingTable;
    static string startSymbol;
    static void handleNonTerminal(const string &symbol, string &currToken, stack<string> &stack,
                                  vector<pair<bool, string>> &output);
    static bool isTerminal(const string &symbol);
    static bool isEmptyCell(const string &symbol, const string &token);
};


#endif //COMPILER_SYNTAXPARSER_H
