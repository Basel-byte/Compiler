#include <bits/stdc++.h>
using namespace std;

class TokenFileWriter{
    private:
        ofstream tokenFile;

    public:
        TokenFileWriter();
        ~TokenFileWriter();
        void tokenEnumWriter(vector<string> defNames, vector<string> ruleNames);
};