#include <bits/stdc++.h>
using namespace std;

class MainFileWriter{
    private:
        ofstream mainFile;
    
    public:
        MainFileWriter();
        ~MainFileWriter();
        void writeMainFileImports();
        void writeMainFileFunction(vector<string> ruleNames);
};  