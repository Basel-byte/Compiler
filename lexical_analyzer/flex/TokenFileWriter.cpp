#include "TokenFileWriter.h"
using namespace std;

TokenFileWriter :: TokenFileWriter(){
    cout << "\nTokenFileWriter Instantiated ...\n";
    tokenFile.open("tokens.h");
}

TokenFileWriter :: ~TokenFileWriter(){
    cout << "TokenFileWriter Finished ...\n";
    tokenFile.close();
}

void TokenFileWriter :: tokenEnumWriter(vector<string> defNames, vector<string> ruleNames){
    cout << "Writing tokens.h ... \n\n";    
    tokenFile << "namespace tokens {\n";
    tokenFile << "  enum tokenName{\n";
    tokenFile << "      EOF_TOK,\n";
    for (string defName : defNames) tokenFile << "      " + defName << ",\n";
    for (string ruleName : ruleNames) tokenFile << "      " + ruleName << ",\n";
    tokenFile << "  };\n";
    tokenFile << "};\n";
}