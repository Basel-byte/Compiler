//
// Created by basel on 12/27/23.
//

#include <stack>
#include "SyntaxParser.h"

LexicalParser* SyntaxParser::lexicalParser;
map<string, map<string, vector<string>>> SyntaxParser::parsingTable;
string SyntaxParser::startSymbol;

string toString(vector<string> & production);

void SyntaxParser::init(LexicalParser &lexicalParser_,
                                    const map<string, map<string, vector<string>>> &parsingTable_,
                                    const string &startSymbol_) {
    lexicalParser = &lexicalParser_;
    parsingTable = parsingTable_;
    startSymbol = startSymbol_;
}

vector<pair<bool, string>> SyntaxParser::parseProgram() {
    vector<pair<bool, string>> derivations;
    stack<string> stack;
    stack.emplace("$");
    stack.push(startSymbol);
    while (stack.size() > 1) {
        string currToken = lexicalParser->getNextToken();
        string currSymbol = stack.top();
        if (isTerminal(currSymbol)) {
            if (currSymbol != currToken)
                derivations.emplace_back(false, "Error: missing " + currSymbol + ", inserted");
            stack.pop();
        }
        else handleNonTerminal(currSymbol, currToken, stack, derivations);
    }
    if (stack.top() == "$" && lexicalParser->getNextToken() == "$")
        derivations.emplace_back(true, "Accepted :)");
    else
        derivations.emplace_back(false, "Error: fail to parse input program :(");
    return derivations;
}

void SyntaxParser::handleNonTerminal(const string &symbol, const string &token,
                                     stack<string> &stack, vector<pair<bool, string>> &derivations) {
    if (isEmptyCell(symbol, token))
        derivations.emplace_back(false, "Error:(illegal " + symbol + ") – discard " + token);
    else {
        stack.pop();
        vector<string> production = parsingTable[symbol][token];
        if (production.size() == 1 && production[0] == "sync")
            derivations.emplace_back(false, "Error: Discard " + symbol);
        else {
            derivations.emplace_back(true, symbol + " ---> " + toString(production));
            if (production.size() != 1 || production[0] != "\\L")
                for (int i = (int) production.size() - 1; i >= 0; i--)
                    stack.push(production[i]);
        }
    }
}

bool SyntaxParser::isTerminal(const string &symbol) {
    return parsingTable.find(symbol) == parsingTable.end();
}

bool SyntaxParser::isEmptyCell(const string &symbol, const string &token) {
    return parsingTable[symbol].find(token) == parsingTable[symbol].end();
}

string toString(vector<string> & production) {
    string prod;
    for (string &symbol : production)
        prod += symbol + " ";
    return prod;
}