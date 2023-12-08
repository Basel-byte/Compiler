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
letter                                           ([a-z]|[A-Z]|"_")
digit                                            ([0-9])
digits                                           ({digit}+)


%%

[ \n\r\t]+                                        {/* ignore white spaces */}
boolean                                           {sPtr = new string(yytext, yyleng);tokenize(BOOLEAN)}
int                                               {sPtr = new string(yytext, yyleng);tokenize(INT)}
float                                             {sPtr = new string(yytext, yyleng);tokenize(FLOAT)}
double                                            {sPtr = new string(yytext, yyleng);tokenize(DOUBLE)}
void                                              {sPtr = new string(yytext, yyleng);tokenize(VOID)}
long                                              {sPtr = new string(yytext, yyleng);tokenize(LONG)}
short                                             {sPtr = new string(yytext, yyleng);tokenize(SHORT)}
byte                                              {sPtr = new string(yytext, yyleng);tokenize(BYTE)}
class                                             {sPtr = new string(yytext, yyleng);tokenize(CLASS)}
interface                                         {sPtr = new string(yytext, yyleng);tokenize(INTERFACE)}
abstract                                          {sPtr = new string(yytext, yyleng);tokenize(ABSTRACT)}
System                                            {sPtr = new string(yytext, yyleng);tokenize(SYSTEM)}
out                                               {sPtr = new string(yytext, yyleng);tokenize(OUT)}
in                                                {sPtr = new string(yytext, yyleng);tokenize(IN)}
print                                             {sPtr = new string(yytext, yyleng);tokenize(PRINT)}
println                                           {sPtr = new string(yytext, yyleng);tokenize(PRINTLN)}
printf                                            {sPtr = new string(yytext, yyleng);tokenize(PRINTF)}
static                                            {sPtr = new string(yytext, yyleng);tokenize(STATIC)}
new                                               {sPtr = new string(yytext, yyleng);tokenize(NEW)}
return                                            {sPtr = new string(yytext, yyleng);tokenize(RETURN)}
do                                                {sPtr = new string(yytext, yyleng);tokenize(DO)}
if                                                {sPtr = new string(yytext, yyleng);tokenize(IF)}
else                                              {sPtr = new string(yytext, yyleng);tokenize(ELSE)}
while                                             {sPtr = new string(yytext, yyleng);tokenize(WHILE)}
;|,|\(|\)|:                                       {sPtr = new string(yytext, yyleng);tokenize(PUNCTUATION)}
("public"|"private"|"protected")                  {sPtr = new string(yytext, yyleng);tokenize(ACCESSMOD)}
(".")                                             {sPtr = new string(yytext, yyleng);tokenize(ACCESS_DOT)}
("Integer"|"Double"|"String"|"Byte"|"Float"|"class"|"Object")                                                  {sPtr = new string(yytext, yyleng);tokenize(DATA_TYPE)}
("true"|"false")                                  {sPtr = new string(yytext, yyleng);tokenize(LOGIC_VALUE)}
("null")                                          {sPtr = new string(yytext, yyleng);tokenize(NIL)}
("import")                                        {sPtr = new string(yytext, yyleng);tokenize(IMPORT)}
("package")                                       {sPtr = new string(yytext, yyleng);tokenize(PACKAGE)}
({letter}({letter}|{digit})*)                     {sPtr = new string(yytext, yyleng);tokenize(ID)}
({digit}+|{digit}+"."{digits}("E"{digits})?)      {sPtr = new string(yytext, yyleng);tokenize(NUM)}
("=="|"!="|">"|">="|"<"|"<=")                     {sPtr = new string(yytext, yyleng);tokenize(RELOP)}
("=")                                             {sPtr = new string(yytext, yyleng);tokenize(ASSIGN)}
("{"|"}")                                         {sPtr = new string(yytext, yyleng);tokenize(CURLY_BRACES)}
("["|"]")                                         {sPtr = new string(yytext, yyleng);tokenize(INDEXING_BRACKET)}
("\""|"\"")                                       {sPtr = new string(yytext, yyleng);tokenize(SQUOTES)}
("'"|"'")                                         {sPtr = new string(yytext, yyleng);tokenize(CQUOTES)}
("&"|"|"|"~"|"^")                                 {sPtr = new string(yytext, yyleng);tokenize(BITWISE)}
("!"|"?")                                         {sPtr = new string(yytext, yyleng);tokenize(LOGIC)}
("+"|"-"|"++"|"--")                               {sPtr = new string(yytext, yyleng);tokenize(ADDOP)}
("*"|"/"|"%")                                     {sPtr = new string(yytext, yyleng);tokenize(MULOP)}
.                                                 {sPtr = new string(yytext, yyleng);ofile << "Non-Matching Input. Applying Panic Mode Recovery and Deleting(" << *sPtr << ")\n";}
<<EOF>>                                           {ofile << "EOF_TOK\n"; tokenize(EOF_TOK);}

%%
