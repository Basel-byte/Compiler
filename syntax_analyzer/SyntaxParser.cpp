//
// Created by basel on 12/27/23.
//

#include <stack>
#include "SyntaxParser.h"

LexicalParser* SyntaxParser::lexicalParser;
map<string, map<string, vector<string>>> SyntaxParser::parsingTable;
string SyntaxParser::startSymbol;

string toString(vector<string> & production);
string stringfyStack(stack<string> stack);

void SyntaxParser::init(LexicalParser &lexicalParser_,
                                    const map<string, map<string, vector<string>>> &parsingTable_,
                                    const string &startSymbol_) {
    lexicalParser = &lexicalParser_;
    parsingTable = parsingTable_;
    startSymbol = startSymbol_;
}


pair<vector<string>, vector<pair<bool, string>>> SyntaxParser::parseProgram() {
    vector<pair<bool, string>> output{};
    vector<string> derivations;
    string terminals;
    stack<string> stack;
    stack.emplace("$");
    stack.push(startSymbol);
    derivations.push_back(stringfyStack(stack));
    string currToken = lexicalParser->getNextToken();
    while (stack.size() > 1) {
        string currSymbol = stack.top();
        if (isTerminal(currSymbol)) {
            terminals += currSymbol + " ";
            if (currSymbol != "'" + currToken + "'")
                output.emplace_back(false, "Error: missing " + currSymbol + ", inserted");
            else currToken = lexicalParser->getNextToken();
            stack.pop();
        }
        else handleNonTerminal(currSymbol, currToken, stack, output);
        derivations.push_back(terminals + stringfyStack(stack));
    }
    if (stack.top() == "$" && lexicalParser->getNextToken() == "$")
        output.emplace_back(true, "Accepted :)");
    else
        output.emplace_back(false, "Error: fail to parse input program :(");
    return {derivations, output};
}

void SyntaxParser::handleNonTerminal(const string &symbol, string &currToken, stack<string> &stack,
                                     vector<pair<bool, string>> &output) {
    if (isEmptyCell(symbol, currToken)) {
        output.emplace_back(false, "Error:(illegal " + symbol + ") – discard " + currToken);
        currToken = lexicalParser->getNextToken();
    }
    else {
        stack.pop();
        vector<string> production = parsingTable[symbol][currToken];
        if (production.size() == 1 && production[0] == "sync")
            output.emplace_back(false, "Error: Discard " + symbol);
        else {
            output.emplace_back(true, symbol + " ---> " + toString(production));
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

string stringfyStack(stack<string> stack) {
    string s;
    while (stack.size() > 1) {
        s += stack.top() + " ";
        stack.pop();
    }
    return s;
}