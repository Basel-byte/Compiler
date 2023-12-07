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
    char c = 0;
    string toRecognize;
    while(toRecognize.empty() && c != -1){
        if(isClosedFile()) return "Input File EOF has been reached!!";
        sourceProgFile.get(c);
        if (sourceProgFile.eof()) c = -1;
        updateMeasures(c);
        toRecognize = traverseDFA(c);
    }
    return toRecognize;
}

string LexicalParser :: traverseDFA(char input) {
    auto it = dFAIterator.getTransitions().find(input);
    if(it == dFAIterator.getTransitions().end() || input == -1 || isspace(input)){ // to PHI state !!
        // No Previous Accepting States
        if(lastAC == nullptr) return panicRecover();
        // There is a previous Accepting State
        string recToken = lastAC->getTokenClass();
        lastStartLine += (isspace(input) && lastStartPos > -1)? lineDiff : 0;
        lastStartCol += (isspace(input) && lastStartPos > -1)? colDiff : 0;
        delete lastAC; lastAC = nullptr;
        dFAIterator = DFA(miniDFA);
        if(input == -1 && !recToken.empty() && lastStartPos < 0) {
            sourceProgFile.clear(ios_base::eofbit);
            lastStartPos++;
        }
        sourceProgFile.seekg((isspace(input) && lastStartPos > -1)? 0 : lastStartPos - 1, ios_base::cur);
        lastStartPos = colDiff = lineDiff = 0;
        return recToken;
    }
    dFAIterator = *dFAIterator.move(input);
    if(dFAIterator.isAcceptingState()) {
        lastAC = new DFA(dFAIterator);
        lastStartCol += colDiff;
        lastStartPos = colDiff = 0;
    }
    else lastStartPos--;
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
    while(lastStartPos < 0 && isspace(c)){
        if(c == '\n') {
            lastStartLine ++;
            lastStartCol = 0;
        }
        else lastStartCol++;
        lastStartPos++;
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
    if(lastStartPos == 0 && (isspace(c))) return "";
    return "PANIC MODE RECOVERY APPLIED: Deleting Character ( " + string(1, c) + " ) At Ln.: "
           + to_string(lastStartLine + 1) + " , Col.: " + to_string(lastStartCol);
}