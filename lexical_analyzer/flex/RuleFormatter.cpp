#include "RuleFormatter.h"

RuleFormatter :: RuleFormatter(){cout << "RuleFormatter instantiated...\n";}
RuleFormatter ::~RuleFormatter(){cout << "RuleFormatter Finished...\n";}

vector<string> RuleFormatter :: getFormattedRules(){return formattedRules;}
vector<string> RuleFormatter :: getRuleNames(){return ruleNames;}

set<string> RuleFormatter :: getDefinitionNames(){return defNames;}
vector<string> RuleFormatter :: getFormattedDefinitions(){return formattedDefs;}

void RuleFormatter :: formatKeywordAndPunc(string filename){
    ifstream file(filename);
    string line;
    if (file.is_open()) {
        while (getline(file, line)) {
            if (line.at(0) == '{') extractKeywords(line);
            else if(line.at(0) == '[') makePunctuationRule(line);
        }
        file.close();
    } 
    else cout << "Unable to open Rules File" << endl;
}

void RuleFormatter :: formatLowPriority(string filename){
    ifstream file(filename);
    string line;
    if (file.is_open()) {
        while (getline(file, line)) {
            if (line.at(0) != '{' && line.at(0) != '[') 
                processREorRD (line);
        }
        file.close();
    } 
    else cout << "Unable to open Rules File" << endl;
}

void RuleFormatter :: extractKeywords(string rule){
    string s;
    rule = rule.substr(1, rule.length() - 2);
    stringstream ss(regex_replace(rule, regex("(\\s+|\\t+)"), " "));
    while(getline(ss, s, ' ')) makeKeywordRule(s);
}

void RuleFormatter :: makeKeywordRule(string keyword){
    if(keyword.empty()) return;
    formattedRules.push_back(keyword);
    transform(keyword.begin(), keyword.end(), keyword.begin(), [](unsigned char c){ return toupper(c); });
    ruleNames.push_back(keyword);
}

void RuleFormatter :: makePunctuationRule(string rule) {
    rule = regex_replace(rule, regex("(\\s+|\\t+)"), " ");
    rule = "\"" + rule.substr(1, rule.length() - 2) + "\"";
    rule = regex_replace(rule, regex(" "), "\" | \"");
    rule = regex_replace(rule, regex(R"("\\(-|=|\+|\*|\(|\)|L|\|))"), "\"$1");

    formattedRules.push_back(rule);
    ruleNames.push_back("PUNCTUATION");
}

void RuleFormatter :: processREorRD(string rule){
    rule = regex_replace(rule, regex("(\\s|\\t)\\:"), ":");
    rule = regex_replace(rule, regex("(\\s|\\t)\\="), "=");

    size_t pos = min(rule.find("="), rule.find(":"));
    string name = rule.substr(0, pos);
    string pattern = rule.substr(pos+1);
    bool isRD = rule.at(pos) == '=';

    pattern = regex_replace(pattern, regex("(\\s+|\\t+)"), " ");
    pattern = regex_replace(pattern, regex("(((\\s|\\t)-(\\s|\\t))|((\\s|\\t)-)|(-(\\s|\\t)))"), "-");
    
    pattern = regex_replace(pattern, regex("(\\(|\\)|\\|)"), " $1 ");
    pattern = regex_replace(pattern, regex("(\\s+|\\t+)"), " ");
    pattern = regex_replace(pattern, regex("(\\s|\\t)\\+"), "+");
    pattern = regex_replace(pattern, regex("(\\s|\\t)\\*"), "*");
    
    makeREorRD(pattern, name, isRD);
}

string RuleFormatter :: processPattern(string pattern){
    stringstream ss(pattern);
    string s;
    vector <string> tokens, formattedTokens;
    while (getline(ss, s, ' ')) tokens.push_back(s);
    for(string t : tokens)
        if(t != "") formattedTokens.push_back(parseToken(t));
    string result = "";
    for(string t : formattedTokens) result += t;
    return result;
}

string RuleFormatter :: parseToken(string pattern){
    if(regex_match(pattern, regex("(\\(|\\)|\\|)"))) return pattern;
    if(pattern == "0-9" || pattern == "a-z" ||pattern == "A-Z") return "[" + pattern + "]";
    if(defNames.find(pattern) != defNames.end()) return "{" + pattern + "}";
    else if(pattern.at(pattern.length() > 1 && pattern.length() - 2) != '\\' && 
            (pattern.at(pattern.length() - 1) == '*' || pattern.at(pattern.length() - 1) == '+')){
        char op = pattern.at(pattern.length() - 1);
        pattern = pattern.substr(0, pattern.length() - 1);
        return parseToken(pattern) + op;  
    }
    return "\"" + regex_replace(pattern, regex(R"(\\(-|=|\+|\*|\(|\)|L|\|))"), "$1") + "\"";
}

string RuleFormatter :: lambdaToOptional(string pattern){
    string result = "(";
    int count = 1; 
    stack<int> lambdas;
    lambdas.push(1);

    for(int i = 0; i < pattern.length(); i++){
        if(pattern.at(i) == '(') { count++; result += '('; }
        else if(pattern.at(i) == ')') {
            result += ')';
            if(lambdas.top() > --count) {
                result += "?";
                lambdas.pop();
            }
        }
        else if(i + 4 < pattern.length() && pattern.substr(i, 4) == "|\"L\"") {
            lambdas.push(count);
            i+=3;
        }
        else if(i + 4 < pattern.length() && pattern.substr(i, 4) == "\"L\"|") {
            lambdas.push(count);
            i+=3;
        }
        else result += pattern.at(i);
    }
    return result + ")";
}

void RuleFormatter :: makeREorRD(string pattern, string name, bool isRD){
    pattern = processPattern(pattern);
    pattern = lambdaToOptional(pattern);
    if(isRD){
        formattedDefs.push_back(pattern);
        defNames.insert(name);
    }
    else{
        formattedRules.push_back(pattern);
        transform(name.begin(), name.end(), name.begin(), [](unsigned char c){ return toupper(c); });
        ruleNames.push_back(name);
    }
}