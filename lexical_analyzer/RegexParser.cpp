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
#include <iostream>

RegexParser::RegexParser() {
    keywordsRegex = regex(R"(\{.*\})");
    punctRegex = regex(R"(\[.*\])");
    rangeLetter = regex("([A-Za-z])-(?!\1)([A-Za-z])");
    rangeDigit = regex("([0-9])-(?!\1)([0-9])");
    epsilonRegex = regex (escapeRegex("\\L"));
    operators = set<char>{'-', '+', '*', '(', ')', '|', '\1'};
    regexMap.insert({"\\L",  ThomsonConstructor::createEpsilon()});
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
        while (getline(ss, word, ' ')) {
            parseRE(word, word);
            PriorityTable::addTokenClass(word, 0);
        }
    }
    else {
        line.erase(remove_if(line.begin(), line.end(), ::isspace),  line.end());
        size_t colonPos = line.find(':');
        size_t equalPos = line.find('=');
        int minPos = min(colonPos, equalPos);
        string lhs = line.substr(0, minPos);
        string rhs = line.substr(minPos + 1, line.length() - minPos - 1);
        parseRE(lhs, rhs);
        if (colonPos < equalPos)
            PriorityTable::addTokenClass(lhs);
    }
}

void RegexParser::parseRE(const string& lhs, string rhs) {
    map<int, string> posToMatch;
    smatch rangeMatch;
    findNonOverlappingMatches(rhs, rangeLetter, posToMatch);
    findNonOverlappingMatches(rhs, rangeDigit, posToMatch);

    for (auto & it : regexMap) {
        string str = it.first;
        if (str.length() == 1)
            continue;
        findAllOccurrences(rhs, regex(escapeRegex(str)), posToMatch);
    }

    vector<pair<char, NFA*>> tokens = tokenize(move(rhs), posToMatch);
    regexMap.insert({lhs, Utility::getCorrespondingNFA(tokens)});
}

vector<pair<char, NFA*>> RegexParser::tokenize(string rhs, map<int, string>& posToMatch) {
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
            string str = posToMatch[i];
            tokens.emplace_back(rhs[i], regexMap[str]);
            i += (int)str.length() - 1;
        }
        else
            tokens.emplace_back(rhs[i], ThomsonConstructor::creatBasic(rhs[i]));
    }
    for (int i = 1; i < tokens.size(); i++) {
        if (isConcat(tokens, i))
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

void RegexParser::findNonOverlappingMatches(const string& input, const regex& reg, map<int, string>& posToMatch) {
    auto words_begin = sregex_iterator(input.begin(), input.end(), reg);
    auto words_end = sregex_iterator();

    for (sregex_iterator i = words_begin; i != words_end; ++i) {
        const smatch& match = *i;
        string range = match.str();
        posToMatch[match.position()] = range;
        if (regexMap.find(range) == regexMap.end())
            regexMap[range] = ThomsonConstructor::range(range[0], range[2]);
    }
}

void RegexParser::findAllOccurrences(const string& input, const regex& reg, map<int, string>& posToMatch) {
    auto words_begin = sregex_iterator(input.begin(), input.end(), reg);
    auto words_end = sregex_iterator();

    for (sregex_iterator i = words_begin; i != words_end; ++i) {
        const smatch& match = *i;
        if (posToMatch.find(match.position()) == posToMatch.end() || posToMatch[match.position()].length() < match.length())
            posToMatch[match.position()] = (string)match.str();
    }
}

bool RegexParser::isConcat(vector<pair<char, NFA*>> &tokens, int i) {
    char c = tokens[i].first, c_prev = tokens[i - 1].first;
    NFA* nfa = tokens[i].second;
    NFA* nfa_prev = tokens[i - 1].second;
    return (nfa != nullptr && (nfa_prev != nullptr || c_prev == ')' || c_prev == '+' || c_prev == '*'))
            || (nfa == nullptr && c == '(' && (nfa_prev != nullptr || c_prev == ')' || Utility::isUnary(c_prev)));
}

string RegexParser::escapeRegex(const string& input) {
    std::string result;
    for (char ch : input) {
        if (ch == '\\') {
            result += "\\\\";
        } else {
            result += ch;
        }
    }
    return result;
}
