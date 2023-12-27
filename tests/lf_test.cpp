//
// Created by basel on 12/27/23.
//

#include "../syntax_analyzer/CFGReader.h"
#include "../syntax_analyzer/LeftFactorer.h"

void run(string path) {
    CFGReader cfgReader(path);
    map<string, vector<vector<string>>> rules = cfgReader.parseRules();
    map<string, vector<vector<string>>> newRules = LeftFactorer::leftFactor(rules);
    for (auto &pair : newRules) {
        cout << pair.first << " = ";
        vector<vector<string>> prods = pair.second;
        for (size_t i = 0; i < prods.size(); i++) {
            for (const string& symbol : prods[i])
                cout << symbol << " ";
            if (i != prods.size() - 1)
                cout << "| ";
        }
        cout << "\n";
    }
}

int main(int argc, char* argv[]) {
    run(argv[1]);
    return 0;
}