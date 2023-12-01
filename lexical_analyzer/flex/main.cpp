#include <bits/stdc++.h>
#include <FlexLexer.h>
#include "tokens.h"
using namespace std;
string* sPtr = nullptr;
extern ofstream ofile;

int main(int argc, char** argv){
   ifstream ifile("program.java");
   yyFlexLexer lexer(&ifile, &ofile);
   while(tokens::tokenName tok = (tokens::tokenName) ( lexer.yylex() )) {
       switch (tok) {
           case tokens::BOOLEAN:
               ofile <<"BOOLEAN("<< *sPtr << ")\n";
               delete sPtr;
               sPtr = nullptr;
               break;
           case tokens::INT:
               ofile <<"INT("<< *sPtr << ")\n";
               delete sPtr;
               sPtr = nullptr;
               break;
           case tokens::FLOAT:
               ofile <<"FLOAT("<< *sPtr << ")\n";
               delete sPtr;
               sPtr = nullptr;
               break;
           case tokens::IF:
               ofile <<"IF("<< *sPtr << ")\n";
               delete sPtr;
               sPtr = nullptr;
               break;
           case tokens::ELSE:
               ofile <<"ELSE("<< *sPtr << ")\n";
               delete sPtr;
               sPtr = nullptr;
               break;
           case tokens::WHILE:
               ofile <<"WHILE("<< *sPtr << ")\n";
               delete sPtr;
               sPtr = nullptr;
               break;
           case tokens::PUNCTUATION:
               ofile <<"PUNCTUATION("<< *sPtr << ")\n";
               delete sPtr;
               sPtr = nullptr;
               break;
           case tokens::ID:
               ofile <<"ID("<< *sPtr << ")\n";
               delete sPtr;
               sPtr = nullptr;
               break;
           case tokens::NUM:
               ofile <<"NUM("<< *sPtr << ")\n";
               delete sPtr;
               sPtr = nullptr;
               break;
           case tokens::RELOP:
               ofile <<"RELOP("<< *sPtr << ")\n";
               delete sPtr;
               sPtr = nullptr;
               break;
           case tokens::ASSIGN:
               ofile <<"ASSIGN("<< *sPtr << ")\n";
               delete sPtr;
               sPtr = nullptr;
               break;
           case tokens::ADDOP:
               ofile <<"ADDOP("<< *sPtr << ")\n";
               delete sPtr;
               sPtr = nullptr;
               break;
           case tokens::MULOP:
               ofile <<"MULOP("<< *sPtr << ")\n";
               delete sPtr;
               sPtr = nullptr;
               break;
       }
   }
    return 0;
}

