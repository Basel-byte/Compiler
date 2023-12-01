#include <bits/stdc++.h>

#include "RuleFormatter.h"
#include "TokenFileWriter.h"
#include "LexWriter.h"
#include "MainFileWriter.h"


using namespace std;

class FlexGenerator{
    private:
        RuleFormatter ruleFormatter;
        TokenFileWriter tokenFileWriter;
        LexWriter lexWriter;
        MainFileWriter mainFileWriter;

        vector<string> ruleNames;
        vector<string> defNames;
        vector<string> formattedRules;
        vector<string> formattedDefs;
        
    public:
        void formatRules();
        void writeTokensFile();
        void writeLexFile();
        void writeMainFile();
};