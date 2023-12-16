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
           case tokens::DOUBLE:
               ofile <<"DOUBLE("<< *sPtr << ")\n";
               delete sPtr;
               sPtr = nullptr;
               break;
           case tokens::VOID:
               ofile <<"VOID("<< *sPtr << ")\n";
               delete sPtr;
               sPtr = nullptr;
               break;
           case tokens::LONG:
               ofile <<"LONG("<< *sPtr << ")\n";
               delete sPtr;
               sPtr = nullptr;
               break;
           case tokens::SHORT:
               ofile <<"SHORT("<< *sPtr << ")\n";
               delete sPtr;
               sPtr = nullptr;
               break;
           case tokens::BYTE:
               ofile <<"BYTE("<< *sPtr << ")\n";
               delete sPtr;
               sPtr = nullptr;
               break;
           case tokens::CLASS:
               ofile <<"CLASS("<< *sPtr << ")\n";
               delete sPtr;
               sPtr = nullptr;
               break;
           case tokens::INTERFACE:
               ofile <<"INTERFACE("<< *sPtr << ")\n";
               delete sPtr;
               sPtr = nullptr;
               break;
           case tokens::ABSTRACT:
               ofile <<"ABSTRACT("<< *sPtr << ")\n";
               delete sPtr;
               sPtr = nullptr;
               break;
           case tokens::SYSTEM:
               ofile <<"SYSTEM("<< *sPtr << ")\n";
               delete sPtr;
               sPtr = nullptr;
               break;
           case tokens::OUT:
               ofile <<"OUT("<< *sPtr << ")\n";
               delete sPtr;
               sPtr = nullptr;
               break;
           case tokens::IN:
               ofile <<"IN("<< *sPtr << ")\n";
               delete sPtr;
               sPtr = nullptr;
               break;
           case tokens::PRINT:
               ofile <<"PRINT("<< *sPtr << ")\n";
               delete sPtr;
               sPtr = nullptr;
               break;
           case tokens::PRINTLN:
               ofile <<"PRINTLN("<< *sPtr << ")\n";
               delete sPtr;
               sPtr = nullptr;
               break;
           case tokens::PRINTF:
               ofile <<"PRINTF("<< *sPtr << ")\n";
               delete sPtr;
               sPtr = nullptr;
               break;
           case tokens::STATIC:
               ofile <<"STATIC("<< *sPtr << ")\n";
               delete sPtr;
               sPtr = nullptr;
               break;
           case tokens::NEW:
               ofile <<"NEW("<< *sPtr << ")\n";
               delete sPtr;
               sPtr = nullptr;
               break;
           case tokens::RETURN:
               ofile <<"RETURN("<< *sPtr << ")\n";
               delete sPtr;
               sPtr = nullptr;
               break;
           case tokens::DO:
               ofile <<"DO("<< *sPtr << ")\n";
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
           case tokens::ACCESSMOD:
               ofile <<"ACCESSMOD("<< *sPtr << ")\n";
               delete sPtr;
               sPtr = nullptr;
               break;
           case tokens::ACCESS_DOT:
               ofile <<"ACCESS_DOT("<< *sPtr << ")\n";
               delete sPtr;
               sPtr = nullptr;
               break;
           case tokens::DATA_TYPE:
               ofile <<"DATA_TYPE("<< *sPtr << ")\n";
               delete sPtr;
               sPtr = nullptr;
               break;
           case tokens::LOGIC_VALUE:
               ofile <<"LOGIC_VALUE("<< *sPtr << ")\n";
               delete sPtr;
               sPtr = nullptr;
               break;
           case tokens::NIL:
               ofile <<"NIL("<< *sPtr << ")\n";
               delete sPtr;
               sPtr = nullptr;
               break;
           case tokens::IMPORT:
               ofile <<"IMPORT("<< *sPtr << ")\n";
               delete sPtr;
               sPtr = nullptr;
               break;
           case tokens::PACKAGE:
               ofile <<"PACKAGE("<< *sPtr << ")\n";
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
           case tokens::CURLY_BRACES:
               ofile <<"CURLY_BRACES("<< *sPtr << ")\n";
               delete sPtr;
               sPtr = nullptr;
               break;
           case tokens::INDEXING_BRACKET:
               ofile <<"INDEXING_BRACKET("<< *sPtr << ")\n";
               delete sPtr;
               sPtr = nullptr;
               break;
           case tokens::SQUOTES:
               ofile <<"SQUOTES("<< *sPtr << ")\n";
               delete sPtr;
               sPtr = nullptr;
               break;
           case tokens::CQUOTES:
               ofile <<"CQUOTES("<< *sPtr << ")\n";
               delete sPtr;
               sPtr = nullptr;
               break;
           case tokens::BITWISE:
               ofile <<"BITWISE("<< *sPtr << ")\n";
               delete sPtr;
               sPtr = nullptr;
               break;
           case tokens::LOGIC:
               ofile <<"LOGIC("<< *sPtr << ")\n";
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

