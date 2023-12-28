//
// Created by basel on 12/28/23.
//

#include "Printer.h"
#include <iostream>

void Printer::printCFG(const string &startSymbol, map<string, vector<vector<string>>> &rules) {
    cout << "\nStart Symbol: " << startSymbol << endl;
    for(const auto& pair : rules){
        cout << "\nNon-Terminal: " << pair.first << endl;
        vector<vector<string>> rulesPerNT = pair.second;
        for (const auto& rule : rulesPerNT) {
            cout << "--> [";
            for (size_t i = 0; i < rule.size(); ++i) {
                cout << rule[i];
                if (i < rule.size() - 1) cout << ", ";
            }
            cout << "]" << endl;
        }
    }
}

void Printer::printTable(const map<string, map<string, vector<string>>> &parsingTable){
    cout <<"\n\n******Parsing Table******\n\n";
    cout << "------------------------------------------------------------------------\n" << endl;
    for(const auto& row : parsingTable){
        cout << "****** " + row.first + " ******\n\n";
        for(const auto&  col : row.second){
            cout << "[ " + col.first + " ] ==> ";
            for(const auto& symbol : col.second){
                cout << symbol << " ";
            }
            cout <<"\n";
        }
        cout << endl << "==================================================================================================" << endl;
    }
}

void Printer::printSet(const map<string, set<string>> &set, const string &s) {
    cout << s + " sets:" << endl;
    for (const auto& entry : set) {
        int count = 0;
        cout << s + "( " <<entry.first << " ) = { " ;
        for (const auto& terminal : entry.second) {
            cout << terminal ;
            count++;
            if(count == entry.second.size())
                cout << " }" << endl;
            else
                cout << ", ";
        }
    }
}


void Printer::printOutput(const vector<pair<bool, string>>& derivations) {
    for (auto &pair : derivations) {
        if (!pair.first)
            cout << "\033[31m";
        else
            cout << "\033[0m";
        cout << pair.second << endl;
    }
}