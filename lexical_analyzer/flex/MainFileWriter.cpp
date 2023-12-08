#include "MainFileWriter.h"
using namespace std;

MainFileWriter :: MainFileWriter(){
    cout << "   MainFileWriter Instantiated ...\n";
    mainFile.open("main.cpp");
}

MainFileWriter :: ~MainFileWriter(){
    mainFile.close();
    cout << "   MainFileWriter Finished ...\n";
}

void MainFileWriter :: writeMainFileImports(){
    cout << "       Writing Main File Imports...\n";
    mainFile << "#include <bits/stdc++.h>\n";
    mainFile << "#include <FlexLexer.h>\n";
    mainFile << "#include \"tokens.h\"\n";

    mainFile << "using namespace std;\n";
    mainFile << "string* sPtr = nullptr;\n";
    mainFile << "extern ofstream ofile;\n\n";
    
}

void MainFileWriter :: writeMainFileFunction(vector<string> ruleNames){
    cout << "       Writing Main File Main Function...\n";
    mainFile << "int main(int argc, char** argv){\n";
    mainFile << "   ifstream ifile(\"program.java\");\n";
    mainFile << "   yyFlexLexer lexer(&ifile, &ofile);\n";
    mainFile << "   while(tokens::tokenName tok = (tokens::tokenName) ( lexer.yylex() )) {\n";
    mainFile << "       switch (tok) {\n";
    for(string name: ruleNames){
        mainFile << "           case tokens::" << name <<":\n";
        mainFile << "               ofile <<\"" << name << "(\"<< *sPtr << \")\\n\";\n";
        mainFile << "               delete sPtr;\n";
        mainFile << "               sPtr = nullptr;\n";
        mainFile << "               break;\n"; 
    }
    mainFile << "       }\n";
    mainFile << "   }\n";
    mainFile << "    return 0;\n";
    mainFile << "}\n\n";
}