//
// Created by basel on 12/28/23.
//

#include "OUtil.h"
#include <iostream>
#include <fstream>

void OUtil::printCFG(const string &startSymbol, map<string, vector<vector<string>>> &rules) {
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

void OUtil::printTable(const map<string, map<string, vector<string>>> &parsingTable){
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

void OUtil::printSet(const map<string, set<string>> &set, const string &s) {
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


void OUtil::printOutput(const vector<pair<bool, string>>& output) {
    for (auto &pair : output) {
        if (!pair.first)
            cout << "\033[31m";
        else
            cout << "\033[0m";
        cout << pair.second << endl;
    }
}

void OUtil::writeDerivations(const vector<string> &derivations, const string &dirpath, const string &programFileName) {
    string path = dirpath + "/" + programFileName + "_left_derivation.txt";
    ofstream ofs(path);

    if (!ofs.is_open()) {
        std::cerr << path << " Output File Not Found!!" << std::endl;
        exit(1); // Return an error code
    }

    for (auto & derivation : derivations)
        ofs << derivation << "\n";
    ofs.close();
}
