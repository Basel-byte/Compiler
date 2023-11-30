#include "TokenFileWriter.h"
using namespace std;

TokenFileWriter :: TokenFileWriter(){cout << "\nTokenFileWriter Instantiated ...\n";}
TokenFileWriter :: ~TokenFileWriter(){cout << "TokenFileWriter Finished ...\n";}

void TokenFileWriter :: tokenEnumWriter(set<string> defNames, vector<string> ruleNames){
    cout << "Writing tokens.h ... \n\n";
    ofstream tokenFile;
    tokenFile.open("tokens.h");
    tokenFile << "namespace tokens {\n";
    tokenFile << "  enum tokenName{\n";
    tokenFile << "      EOF_TOK,\n";
    for (string defName : defNames) tokenFile << "      " + defName << ",\n";
    for (string ruleName : ruleNames) tokenFile << "      " + ruleName << ",\n";
    tokenFile << "  };\n";
    tokenFile << "};\n";
    tokenFile.close();
}