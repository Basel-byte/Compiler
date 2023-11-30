#include <bits/stdc++.h>
#include "RuleFormatter.h"
#include "TokenFileWriter.h"
#include "LexWriter.h"
using namespace std;

int main(int argc, char** argv){
    RuleFormatter ruleFormatter;
    ruleFormatter.formatKeywordAndPunc("rules.txt");
    ruleFormatter.formatLowPriority("rules.txt");

    vector<string> formattedDefinitions = ruleFormatter.getFormattedDefinitions();
    vector<string> definitionNames = ruleFormatter.getDefinitionNames();
    
    vector<string> formattedRules = ruleFormatter.getFormattedRules();
    vector<string> ruleNames = ruleFormatter.getRuleNames();
    
    string space = "                  ";
    cout << "\nRegular Definitions:\n---------------------\n";
    for(int i = 0; i < definitionNames.size(); i++)
        cout << definitionNames.at(i) << space.substr(0, space.length() - definitionNames.at(i).length()) << formattedDefinitions.at(i) << endl;
    
    cout << "\nRegular Expressions:\n---------------------\n";
    for(int i = 0; i < ruleNames.size(); i++)
        cout << ruleNames.at(i) << space.substr(0, space.length() - ruleNames.at(i).length()) << formattedRules.at(i) << endl;
    
    TokenFileWriter tokenFileWriter;
    tokenFileWriter.tokenEnumWriter(definitionNames, ruleNames);

    LexWriter lexWriter;
    lexWriter.writeDefinitionsSection();
    lexWriter.writeRegularDefinitions(definitionNames, formattedDefinitions);
    lexWriter.writeRegularExpressions(ruleNames, formattedRules);
    
    return 0;
}