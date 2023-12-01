%{

#include <iostream>
#include <fstream>
#include "tokens.h"
using namespace std;

#define tokenize(T) return tokens::T;
extern string* sPtr;
extern ofstream ofile("output.txt");

%}

%option noyywrap c++
letter                                           ([a-z]|[A-Z])
digit                                            ([0-9])
digits                                           ({digit}+)


%%

[ \n\r\t]+                                        {/* ignore white spaces */}
boolean                                           {sPtr = new string(yytext, yyleng);tokenize(BOOLEAN)}
int                                               {sPtr = new string(yytext, yyleng);tokenize(INT)}
float                                             {sPtr = new string(yytext, yyleng);tokenize(FLOAT)}
if                                                {sPtr = new string(yytext, yyleng);tokenize(IF)}
else                                              {sPtr = new string(yytext, yyleng);tokenize(ELSE)}
while                                             {sPtr = new string(yytext, yyleng);tokenize(WHILE)}
;|,|\(|\)|\{|\}|\[|\]                             {sPtr = new string(yytext, yyleng);tokenize(PUNCTUATION)}
({letter}({letter}|{digit})*)                     {sPtr = new string(yytext, yyleng);tokenize(ID)}
({digit}+|{digit}+"."{digits}("E"{digits})?)      {sPtr = new string(yytext, yyleng);tokenize(NUM)}
("=="|"!="|">"|">="|"<"|"<=")                     {sPtr = new string(yytext, yyleng);tokenize(RELOP)}
("=")                                             {sPtr = new string(yytext, yyleng);tokenize(ASSIGN)}
("+"|"-")                                         {sPtr = new string(yytext, yyleng);tokenize(ADDOP)}
("*"|"/")                                         {sPtr = new string(yytext, yyleng);tokenize(MULOP)}
.                                                 {sPtr = new string(yytext, yyleng);ofile << "Non-Matching Input. Applying Panic Mode Recovery and Deleting(" << *sPtr << ")\n";}
<<EOF>>                                           {ofile << "EOF_TOK\n"; tokenize(EOF_TOK);}

%%
