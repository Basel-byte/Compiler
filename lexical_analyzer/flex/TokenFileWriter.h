#include <bits/stdc++.h>
using namespace std;

class TokenFileWriter{
    private:
        ofstream tokenFile;

    public:
        TokenFileWriter();
        ~TokenFileWriter();
        void writeTokens(vector<string> ruleNames);
};