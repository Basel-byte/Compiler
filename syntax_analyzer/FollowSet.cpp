// Created by Habiba on 12/23/2023.
//

/**
 * Follow Set Calculation using Iterative Algorithm
 *
 * Rules:
 * 1) If S is the start symbol, $ is in FOLLOW(S)
 * 2) if A -> D B E is a production rule
 *    - everything in FIRST(E) is FOLLOW(B) except Є
 * 3) If ( A -> D B is a production rule ) or ( A -> D B E is a production rule and Є is in FIRST(E) ) "rightmost"
 *    - everything in FOLLOW(A) is in FOLLOW(B).
 */

#include "FollowSet.h"

using namespace std;

map<string, set<string>>
FollowSet::followSet(map<string, vector<vector<string>>> rules, map<string, set<string>> firstSet, string startSymbol) {
    map<string, set<string>> followSetMap;

    // Case: start symbol
    followSetMap[startSymbol].insert("$");

    // Iterative Algorithm
    bool converge = false;
    int iteration = 0;

    while (!converge || iteration < 4) {
        iteration++;
        map<string, set<string>> prevFollowSetMap = followSetMap;

        for (auto const &x: rules) {
            string nonTerminal = x.first;

            for (auto production: x.second) {
                int i = 0;
                while (i < production.size()) {
                    auto nextSymbol = production[i];

                    // Skip non-terminals
                    while (i < production.size() - 1 && nextSymbol[0] == '\'') {
                        i++;
                        nextSymbol = production[i];
                    }

                    // First non-terminal
                    i++;
                    if (i < production.size()) {
                        nextSymbol = production[i];
                        // terminal
                        if (nextSymbol[0] == '\'')
                            followSetMap[production[i - 1]].insert(nextSymbol.substr(1, nextSymbol.size() - 2));
                        else { // case nonterminal
                            //non terminal followed by non terminal ex A B
                            // follow A is first of B

                            set<string> first = firstSet[nextSymbol];
                            followSetMap[production[i - 1]].insert(first.begin(), first.end());

                            // epsilon handling

                            //if first of B has epsilon ex A B C
                            // follow A is first of C also
                            // i-1 -> B  index = i+1 -> C
                            int index = i + 1; // to get first
                            while (followSetMap[production[i - 1]].find("\\L") !=
                                   followSetMap[production[i - 1]].end() &&
                                   index < production.size()) {
                                followSetMap[production[i - 1]].erase("\\L");

                                if (production[index][0] == '\'') //case terminal insert it directly
                                    followSetMap[production[i - 1]].insert(
                                            production[index].substr(1, production[index].size() - 2));
                                else {
                                    // If the next symbol in the production is a non-terminal,
                                    // retrieve the FIRST set of that non-terminal.
                                    set<string> nextFollow = firstSet[production[index]];
                                    followSetMap[production[i - 1]].insert(nextFollow.begin(), nextFollow.end());
                                }
                                index++;
                            }

                            if (followSetMap[production[i - 1]].find("\\L") != followSetMap[production[i - 1]].end()) {
                                followSetMap[production[i - 1]].erase("\\L");
                                // Retrieve the FOLLOW set of the current non-terminal (nonTerminal).
                                set<string> currentFollow = followSetMap[nonTerminal];
                                // Insert the FOLLOW set of the current non-terminal into the FOLLOW set of the preceding non-terminal.
                                followSetMap[production[i - 1]].insert(currentFollow.begin(), currentFollow.end());
                            }
                        }
                    }
                }
                // last symbol then add header of production
                //  Rule 3 :case it is not terminal and rightmost so the follow of production terminal is same
                if (production[production.size() - 1][0] != '\'' && production[production.size() - 1] != "\\L") {
                    set<string> headerFollow = followSetMap[nonTerminal];
                    followSetMap[production[production.size() - 1]].insert(headerFollow.begin(), headerFollow.end());
                }
            }
        }

        // Convergence update
        int nTCount = 0;

        // Check if the sizes of FOLLOW sets have changed for each non-terminal
        for (auto nT: prevFollowSetMap) {
            int prevSize = nT.second.size();
            int currentSize = followSetMap[nT.first].size();

            // If the size of any FOLLOW set has changed, exit the loop
            if (prevSize != currentSize)
                break;

            nTCount++;
        }

        // If compares the sizes of the FOLLOW sets before and after the iteration for each non-terminal.
        // If the size of any FOLLOW set has changed, the converge variable remains false, indicating that there may still be changes.
        // If the size of all FOLLOW sets remains the same, the converge variable is set to true, indicating that no further changes are occurring.
        if (nTCount == prevFollowSetMap.size())
            converge = true;
    }

    return followSetMap;
}
