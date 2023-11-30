#include "LexWriter.h"
using namespace std;

LexWriter :: LexWriter(){
    cout << "LexWiter Instantiated ...\n";
    lexFile.open("flex.l");
}
LexWriter :: ~LexWriter(){
    lexFile.close();
    cout << "LexWiter Finished ... \n";
}

void LexWriter :: writeDefinitionsSection(){
    cout << "Writing Definitions and Including Needed Libraries ...\n";
    lexFile << "%{\n\n";
    
    lexFile << "#include <iostream>\n";
    lexFile << "#include \"tokens.h\"\n";
    lexFile << "using namespace std;\n\n";
    lexFile << "#define tokenize(T) return tokens::T;\n";
    lexFile << "extern string* sPtr;\n\n";

    lexFile << "%}\n\n";
}

void LexWriter :: writeRegularDefinitions(vector<string> defNames, vector<string> defFormats){
    cout << "Writing Regular Definitions ...\n";
    lexFile << "%option noyywrap c++\n";
    string space = "                                                 ";
    for (int i = 0; i < defNames.size(); i++){
        int length = space.length() - defNames.at(i).length();
        lexFile << defNames.at(i) << space.substr(0, length) << defFormats.at(i) << "\n";   
    }
    lexFile << "\n";
}

void LexWriter :: writeRegularExpressions(vector<string> ruleNames, vector<string> ruleFormats){
    cout << "Writing Regular Expressions and their Associated Action ...\n";
    
    string inputString = "sPtr = new string(yytext, yyleng);";
    lexFile << "\n%%\n\n";
    
    int length;
    string space = "";
    for(int i = 0; i < 50; i++) space += " ";
    
    length =  max((unsigned long)1, space.length() - 10);
    lexFile << "[ \\n\\r\\t]+" << space.substr(0, length) << "{/* ignore white spaces */}\n";

    for(int i = 0; i < ruleNames.size(); i++){
        length =  max((unsigned long)1, space.length() - ruleFormats.at(i).length());
        lexFile << ruleFormats.at(i) << space.substr(0, length);
        lexFile << "{" << inputString << "tokenize(" << ruleNames.at(i) << ")}\n";
    }

    length =  max((unsigned long)1, space.length() - 1);
    lexFile << "." << space.substr(0, length) << "{";
    lexFile << inputString << "cout << \"Non-Matching Input. Applying Panic Mode Recovery and Deleting(\" << *sPtr << \")\\n\";}\n";
    
    length =  max((unsigned long)1, space.length() - 7);
    lexFile << "<<EOF>>" << space.substr(0, length) << "{cout<< \"EOF_TOK\\n\"; tokenize(EOF_TOK);}\n";
    
    lexFile << "\n%%\n";
}