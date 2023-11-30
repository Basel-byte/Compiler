#include <bits/stdc++.h>
using namespace std;

class RuleFormatter{
    private:
        vector<string> formattedRules;
        vector<string> ruleNames;
        set<string> defNamesSet;
        vector<string> defNames;
        vector<string> formattedDefs;
        
        void extractKeywords(string rule);
        void makeKeywordRule(string keyword);
        void makePunctuationRule(string rule);

        void makeREorRD(string pattern, string name, bool isRD);
        void processREorRD(string rule);
        string processPattern(string pattern);
        string parseToken(string pattern);

        string lambdaToOptional(string pattern);

    public:
        RuleFormatter();
        ~RuleFormatter();
        vector<string> getFormattedRules();
        vector<string> getRuleNames();
        
        vector<string> getDefinitionNames();
        vector<string> getFormattedDefinitions();
        
        void formatKeywordAndPunc(string filename);
        void formatLowPriority(string filename);
};