//
// Created by louay on 12/23/23.
//

#include "CFGReader.h"
using namespace std;

CFGReader :: CFGReader(string& CFGFilePath) {
    CFGFile.open(CFGFilePath);
    if (!CFGFile.is_open()){
        cout << "CFG File Not Found!!";
        exit(1);
    }

}

string CFGReader :: getStartSymbol(){return startSymbol;}


map<string, vector<vector<string>>> CFGReader :: parseRules() {
    map<string, vector<vector<string>>> rules;
    string line, currentNT;
    regex assignPattern("="), pipePattern("\\| ");
    smatch matcher;
    while (getline(CFGFile, line)){
        line = adjustWhiteSpaces(line);
        if(line[0] == '#' && regex_search(line, matcher, assignPattern)) { // a new rule
            size_t position = matcher.position();
            currentNT = line.substr(2, position - 3); // 2 because of # + space and pos - 3 because of space + =
            if(startSymbol.empty()) startSymbol = currentNT;
            string productions = line.substr(position + 2); // pos + 2 because of = + space
            rules[currentNT] = productionToVector(productions);
        }
        else if(regex_search(line, matcher, pipePattern)){ // the rest of the previous productions
            size_t position = matcher.position();
            string restOfProduction = line.substr(position + 2);
            vector<vector<string>> ruleVector = productionToVector(restOfProduction);
            for(const auto & i : ruleVector) rules[currentNT].push_back(i);
        }
    }
    CFGFile.close();
    return rules;
}

vector<vector<string>> CFGReader :: productionToVector(string& production){
    vector<vector<string>> unionedRules;
    vector<string> concatRules = splitOn(production, " \\| ");

    for(const string& concatRule : concatRules){
        vector<string> terminalsNonTerminals = splitOn(concatRule, " ");
        unionedRules.push_back(terminalsNonTerminals);
    }
    return unionedRules;
}

vector<string> CFGReader:: splitOn(string toSplit, const string& separator){
    vector<string> result;
    regex sepRegex(separator);
    sregex_token_iterator iter(toSplit.begin(), toSplit.end(), sepRegex, -1);
    sregex_token_iterator end;
    while (iter != end) {
        result.push_back(*iter);
        ++iter;
    }
    return result;
}

string CFGReader ::adjustWhiteSpaces(const string& toAdjust) {
    return regex_replace(toAdjust, regex("\\s+"), " ");
}