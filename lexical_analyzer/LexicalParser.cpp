//
// Created by louay on 12/4/23.
//

#include "LexicalParser.h"
using namespace std;

LexicalParser :: LexicalParser(const DFA &miniDFA, const string &srcPrgPath): miniDFA(miniDFA), dFAIterator(miniDFA) {
    sourceProgFile.open(srcPrgPath);
    if (!sourceProgFile.is_open()){
        cout << "Source Program File Not Found!!";
        exit(1);
    }
    lastStartDiff = lineDiff = colDiff = lastStartLine = lastStartCol = 0;
    lastAC = nullptr;
}

LexicalParser :: ~LexicalParser() = default;

bool LexicalParser :: isClosedFile() {return !sourceProgFile.is_open();}

void LexicalParser :: closeFile() {sourceProgFile.close();}

void LexicalParser :: updateLnColDiff(char input) {
    if(input == '\n') {
        lineDiff++;
        colDiff = -lastStartCol;
    }
    else colDiff++;
}

string LexicalParser :: getNextToken(){
    char c = 0;
    string toRecognize;
    string token;
    while(toRecognize.empty() && c != -1){
        token += c;
        if(isClosedFile()) return "$";
        sourceProgFile.get(c);
        if (sourceProgFile.eof()) c = -1;
        updateLnColDiff(c);
        toRecognize = traverseDFA(c);
        if(c == -1 && lastStartDiff == 0) {
            closeFile();
            return "$";
        }
    }
    token = token.substr(1, token.size());
    tokens.push_back(token);
    return toRecognize;
}
string LexicalParser :: traverseDFA(char input) {
    auto it = dFAIterator.getTransitions().find(input);
    if(it == dFAIterator.getTransitions().end() || input == -1 || isspace(input)){ // to PHI state !!
        // No Previous Accepting States
        if(lastAC == nullptr) return panicRecover();
        // There is a previous Accepting State
        string recToken = lastAC->getTokenClass();
        lastStartLine += (isspace(input) && lastStartDiff > -1) ? lineDiff : 0;
        lastStartCol += (isspace(input) && lastStartDiff > -1) ? colDiff : 0;
        delete lastAC; lastAC = nullptr;
        dFAIterator = DFA(miniDFA);
        if(input == -1 && !recToken.empty() && lastStartDiff < 0) {
            sourceProgFile.clear(ios_base::eofbit);
            lastStartDiff++;
        }
        sourceProgFile.seekg((isspace(input) && lastStartDiff > -1) ? 0 : lastStartDiff - 1, ios_base::cur);
        lastStartDiff = colDiff = lineDiff = 0;
        return recToken;
    }
    dFAIterator = *dFAIterator.move(input);
    if(dFAIterator.isAcceptingState()) {
        lastAC = new DFA(dFAIterator);
        lastStartCol += colDiff;
        lastStartDiff = colDiff = 0;
    }
    else lastStartDiff--;
    return "";
}

void LexicalParser :: writeAllTokens(const string &outFileName){
    parsedTokenFile.open(outFileName);
    while(!isClosedFile()) {
        string tokenClass = getNextToken();
        if (tokenClass == "$")
            parsedTokenFile << "Input File EOF has been reached!!" << endl;
        else
            parsedTokenFile << tokenClass << endl;
    }
    parsedTokenFile.close();
}

string LexicalParser :: panicRecover() {
    char c;
    sourceProgFile.seekg(lastStartDiff - 1, ios_base::cur);
    sourceProgFile.get(c);
    while(lastStartDiff < 0 && isspace(c)){
        if(c == '\n') {
            lastStartLine ++;
            lastStartCol = 0;
        }
        else lastStartCol++;
        lastStartDiff++;
        sourceProgFile.get(c);
    }
    if(sourceProgFile.eof() || c == -1) {
        closeFile();
        return "Input File EOF has been reached!!";
    }
    if(c == '\n') {
        lastStartLine++;
        lastStartCol = 0;
    }
    else lastStartCol++;
    colDiff = lineDiff = 0;
    dFAIterator = DFA(miniDFA);
    if(lastStartDiff == 0 && (isspace(c))) return "";
    return "PANIC MODE RECOVERY APPLIED: Deleting Character ( " + string(1, c) + " ) At Ln.: "
           + to_string(lastStartLine + 1) + " , Col.: " + to_string(lastStartCol);
}