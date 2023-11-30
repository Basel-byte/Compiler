#include <bits/stdc++.h>
using namespace std;

class TokenFileWriter{
    public:
        TokenFileWriter();
        ~TokenFileWriter();
        void tokenEnumWriter(set<string> defNames, vector<string> ruleNames);
};