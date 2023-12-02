//
// Created by Dell on 01/12/2023.
//

#include "RegexParser.h"
#include <utility>
#include "ThomsonConstructor.h"
#include "PriorityTable.h"
#include "Utility.h"
#include <string>
#include <fstream>

RegexParser::RegexParser() {
    keywordsRegex = regex(R"(\{.*\})");
    punctRegex = regex(R"(\[.*\])");
    rangeLetter = regex(R"([A-Za-z])-(?!\1)([A-Za-z])");
    rangeDigit = regex(R"([0-9])-(?!\1)([0-9]))");
    operators = set<char>{'-', '+', '*', '(', ')', '|', '\1'};
    regexMap["\\L"] = ThomsonConstructor::createEpsilon();
}

NFA* RegexParser::parseREs(const string& filepath) {
    fstream file;
    file.open(filepath, ios::in);
    if (file.is_open()) {
        string line;
        while (getline(file, line))
            parseLine(line);
        file.close();
    }
    return getCombinedNFA();
}


void RegexParser::parseLine(string line) {
    if (regex_match(line, punctRegex))
        parsePunctuationSymbols(line.substr(1, line.length() - 2));
    else if (regex_match(line, keywordsRegex)) {
        stringstream ss(line.substr(1, line.length() - 2));
        string word;
        while (getline(ss, word, ' '))
            parseRE(word, word);
    }
    else {
        line.erase(remove_if(line.begin(), line.end(), ::isspace),  line.end());
        int colonPos = line.find(':');
        int equalPos = line.find('=');
        int minPos = min(colonPos, equalPos);
        string lhs = line.substr(0, minPos);
        string rhs = line.substr(minPos + 1, line.length() - minPos - 1);
        parseRE(lhs, rhs);
        if (colonPos < equalPos)
            PriorityTable::addTokenClass(lhs);
    }

}

void RegexParser::parseRE(const string& lhs, string rhs) {
    map<int, smatch> posToMatch;
    smatch rangeMatch;
    if (regex_search(rhs, rangeMatch, rangeDigit)) {
        posToMatch[rangeMatch.position()] = rangeMatch;
        string range = rangeMatch.str();
        regexMap[range] = ThomsonConstructor::range(range[0], range[2]);
    }
    if (regex_search(rhs, rangeMatch, rangeLetter)) {
        posToMatch[rangeMatch.position()] = rangeMatch;
        string range = rangeMatch.str();
        regexMap[range] = ThomsonConstructor::range(range[0], range[2]);
    }
    for (auto & it : regexMap) {
        smatch match;
        if (regex_search(rhs, match, regex(it.first))) {
            if (posToMatch.find(match.position()) == posToMatch.end() || posToMatch[match.position()].length() < match.length())
                posToMatch[match.position()] = match;
        }
    }
    vector<pair<char, NFA*>> tokens = tokenize(move(rhs), posToMatch);
    regexMap[lhs] = Utility::getCorrespondingNFA(tokens);
}

vector<pair<char, NFA*>> RegexParser::tokenize(string rhs, map<int, smatch> posToMatch) {
    vector<pair<char, NFA*>> tokens;
    for (int i = 0; i < rhs.length(); i++) {
        if (isOperator(rhs[i])) {
            if (!tokens.empty() && tokens.back().first == '\\') {
                tokens.pop_back();
                tokens.emplace_back(rhs[i], ThomsonConstructor::creatBasic(rhs[i]));
            }
            else
                tokens.emplace_back(rhs[i], nullptr);
        }
        else if (posToMatch.find(i) != posToMatch.end()) {
            smatch match = posToMatch[i];
            tokens.emplace_back(rhs[i], regexMap[match.str()]);
            i += match.length() - 1;
        }
        else
            tokens.emplace_back(rhs[i], ThomsonConstructor::creatBasic(rhs[i]));
    }
    for (int i = 1; i < tokens.size(); i++) {
        if (tokens[i].second != nullptr && tokens[i - 1].second != nullptr)
            tokens.insert(tokens.begin() + i, pair<char, NFA*>('\1', nullptr));
    }
    return tokens;
}

void RegexParser::parsePunctuationSymbols(string symbols) {
    for (int i = 0; i < symbols.length(); i++) {
        if (isOperator(symbols[i]) && i > 0 && symbols[i - 1] != '\\')
            throw exception();
        else if (symbols[i] != '\\' || (i == symbols.length() - 1 || !isOperator(symbols[i + 1]))) {
            string token = string(1, symbols[i]);
            regexMap[token] = ThomsonConstructor::creatBasic(symbols[i]);
            PriorityTable::addTokenClass(token);
        }
    }
}

bool RegexParser::isOperator(char c) {
    return this->operators.find(c) != this->operators.end();
}

NFA* RegexParser::getCombinedNFA() {
    vector<pair<string, NFA*>> nfas;
    for (auto &it : PriorityTable::table)
        nfas.emplace_back(it.first, regexMap[it.first]);
    return ThomsonConstructor::getCombinedNFA(nfas);
}

