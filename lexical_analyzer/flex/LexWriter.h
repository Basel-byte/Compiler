#include <bits/stdc++.h>
using namespace std;

class LexWriter{
    private:
        ofstream lexFile;

    public:
        LexWriter();
        ~LexWriter();
        void writeDefinitionsSection();
        void writeRegularDefinitions(vector<string> defNames, vector<string> defFormats);
        void writeRegularExpressions(vector<string> ruleNames, vector<string> ruleFormats);
};