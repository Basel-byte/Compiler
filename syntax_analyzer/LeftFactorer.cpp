//
// Created by basel on 12/26/23.
//

#include <algorithm>
#include "LeftFactorer.h"

map<string, vector<vector<string>>> LeftFactorer::leftFactor(map<string, vector<vector<string>>> &rules) {
    set<string> NTs = getNTs(rules);
    vector<pair<string, vector<vector<string>>>> newRules;
    for (auto &rule : rules) {
        vector<pair<string, vector<vector<string>>>> bunchOfRules = leftFactor(rule, NTs);
        newRules.insert(newRules.begin(), bunchOfRules.begin(), bunchOfRules.end());
    }

    map<string, vector<vector<string>>> leftFactoredRules;
    for (auto &rule : newRules)
        leftFactoredRules[rule.first] = rule.second;
    return leftFactoredRules;
}

vector<pair<string, vector<vector<string>>>>
LeftFactorer::leftFactor(pair<string, vector<vector<string>>> productions, set<string> &NTs) {
    vector<pair<string, vector<vector<string>>>> rules{std::move(productions)};
    size_t i = 0;
    while (i < rules.size()) {
        pair<string, vector<vector<string>>> rule = rules[i];
        string NT = rule.first;
        vector<vector<string>> prods = rule.second;
        sortProductions(prods);
        vector<vector<string>> substitutes;
        size_t j = 0;
        while (j < prods.size()) {
            pair<size_t, pair<size_t, size_t>> matches = getMatches(j, prods);
            size_t matchSize = matches.first, end = matches.second.second;
            if (j + 1 == end)
                substitutes.push_back(prods[j]);
            else {
                string newNT = findSymbolToTheNewNT(NT, NTs);
                vector<string> substitute(prods[j].begin(), prods[j].begin() + matchSize);
                substitute.push_back(newNT);
                substitutes.push_back(substitute);
                rules.push_back(createNewProductions(newNT, matches, prods));
            }
            j = end;
        }
        rules[i].second = substitutes;
        i++;
    }
    return rules;
}

void LeftFactorer::sortProductions(vector<vector<string>> &productions) {
    sort(productions.begin(), productions.end(), [](const auto& a, const auto& b) { return a < b; });
}

pair<size_t, pair<size_t, size_t>> LeftFactorer::getMatches(size_t index, vector<vector<string>> &productions) {
    size_t matchSize = productions[index].size();
    size_t end = index + 1;
    while (end < productions.size()) {
        size_t size = getMaxMatch(matchSize, index, end, productions);
        if (size == 0)
            break;
        matchSize = min(matchSize, size);
        end++;
    }
    return {matchSize, {index, end}};
}

size_t LeftFactorer::getMaxMatch(size_t matchSize, size_t i, size_t j, vector<vector<string>> &productions) {
    size_t k = 0;
    vector<string> production_i = productions[i], production_j = productions[j];
    while (k < matchSize && k < production_j.size() && production_i[k] == production_j[k])
        k++;
    return k;
}

pair<string, vector<vector<string>>>
LeftFactorer::createNewProductions(const string &NT, pair<size_t, pair<int, int>> matches, vector<vector<string>> &productions) {
    pair<string, vector<vector<string>>> newProductions{NT, vector<vector<string>>()};
    size_t matchSize = matches.first;
    int i = matches.second.first, j = matches.second.second;
    for (int k = i; k < j; k++) {
        if (productions[k].begin() + (int) matchSize == productions[k].end())
            newProductions.second.push_back({"\\L"});
        else
            newProductions.second.emplace_back(productions[k].begin() + (int) matchSize, productions[k].end());
    }
    return newProductions;
}

string LeftFactorer::findSymbolToTheNewNT(const string& NT, set<string> &NTs) {
    string newNT = NT + '`';
    while (NTs.find(newNT) != NTs.end())
        newNT += '`';
    NTs.insert(newNT);
    return newNT;
}

set<string> LeftFactorer::getNTs(map<string, vector<vector<string>>> &rules) {
    set<string> NTs;
    for (auto &it : rules)
        NTs.insert(it.first);
    return NTs;
}
