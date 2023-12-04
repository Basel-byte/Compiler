//
// Created by louay on 12/4/23.
//

#include "LexicalParser.h"
using namespace std;

LexicalParser :: LexicalParser(const DFA &miniDFA, string srcPrgPath): miniDFA(miniDFA), dFAIterator(miniDFA) {
    sourceProgFile.open(srcPrgPath);
    if (!sourceProgFile.is_open()){
        cout << "Source Program File Not Found!!";
        exit(1);
    }
    lastStartPos = lineDiff = colDiff = lastStartLine = lastStartCol = 0;
    lastAC = nullptr;
}

LexicalParser :: ~LexicalParser() = default;

bool LexicalParser :: isClosedFile() {return !sourceProgFile.is_open();}

void LexicalParser :: closeFile() {sourceProgFile.close();}

void LexicalParser :: updateMeasures(char input) {
    if(input == '\n') {
        lineDiff++;
        colDiff = -lastStartCol;
    }
    else colDiff++;
}

string LexicalParser :: getNextToken(){
    string toRecognize;
    while(toRecognize.empty()){
        if(isClosedFile()) return "Input File EOF has been reached!!";
        char c;
        sourceProgFile.get(c);
        if (sourceProgFile.eof()) {
            closeFile();
            c = -1;
        }
        updateMeasures(c);
        if(c == '\r' || c == '\t' || c == '\n' || c == ' ') {
            lastStartPos--;
            continue;
        }
        toRecognize = traverseDFA(c);
    }
    return toRecognize;
}

string LexicalParser :: traverseDFA(char input) {
    auto it = dFAIterator.getTransitions().find(input);
    if(it == dFAIterator.getTransitions().end() || input == -1){ // to PHI state !!
        if(lastAC == nullptr) return panicRecover();
        string recToken = lastAC->getTokenClass();
        lastStartLine += lineDiff;
        lastStartCol += colDiff - 1;
        lastStartPos = colDiff = lineDiff = 0;
        delete lastAC; lastAC = nullptr;
        dFAIterator = DFA(miniDFA);
        sourceProgFile.seekg(-1, ios_base::cur);
        return recToken;
    }
    dFAIterator = *dFAIterator.move(input);
    lastStartPos--;
    if(dFAIterator.isAcceptingState()) lastAC = new DFA(dFAIterator);
    return "";
}


void LexicalParser :: writeAllTokens(string outFileName) {
    parsedTokenFile.open(outFileName);
    while(!isClosedFile()) parsedTokenFile << getNextToken() << endl;
    parsedTokenFile.close();
}

string LexicalParser :: panicRecover() {
    char c;
    sourceProgFile.seekg(lastStartPos - 1, ios_base::cur);
    sourceProgFile.get(c);
    while(c == '\r' || c == '\t' || c == '\n' || c == ' '){
        if(c == '\n') {
            lastStartLine ++;
            lastStartCol = 0;
        }
        else lastStartCol++;
        sourceProgFile.get(c);
    }
    if(sourceProgFile.eof() || c == -1) {
        closeFile();
        return "Input File EOF has been reached!!";
    }
    lastStartCol++;
    lastStartPos = colDiff = lineDiff = 0;
    dFAIterator = DFA(miniDFA);
    return "PANIC MODE RECOVERY APPLIED: Deleting Character ( " + string(1, c) + " ) At Ln.: "
           + to_string(lastStartLine + 1) + " , Col.: " + to_string(lastStartCol);
}