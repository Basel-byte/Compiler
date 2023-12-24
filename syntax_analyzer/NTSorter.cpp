//
// Created by louay on 12/24/23.
//

#include "NTSorter.h"
using namespace std;


NTSorter ::NTSorter() = default;

NTSorter :: NTSorter(map<string, vector<vector<string>>> rules) {
    int index = 0;
    for(const auto& pair : rules) NT_index[pair.first] = ++index;

    adjacencyMatrix.assign(index, vector<bool>(index, false));
    for(const auto& pair : rules){
        string source = pair.first;
        vector<vector<string>> oredRules = pair.second;
        for(const auto& rule : oredRules) {
            if (NT_index[rule[0]] > 0)
                adjacencyMatrix[NT_index[source] - 1][NT_index[rule[0]] - 1] = true;
        }
    }
    for (int i = 0; i < adjacencyMatrix.size(); i++) adjacencyMatrix[i][i] = true;
}

void NTSorter :: applyFloydWarshall(){
    for (int k = 0; k < adjacencyMatrix.size(); k++)
        for (int i = 0; i < adjacencyMatrix.size(); i++)
            for (int j = 0; j < adjacencyMatrix.size(); j++)
                adjacencyMatrix[i][j] = adjacencyMatrix[i][j] || (adjacencyMatrix[i][k] && adjacencyMatrix[k][j]);
}

vector<string> NTSorter :: getNTSorted(){
    // Getting Left Corners of each NT and sorting descendingly according to #Left Corners for each Node
    vector<pair<int, int>> indicesCounts;
    for(int i = 0; i < adjacencyMatrix.size(); i++)
        indicesCounts.emplace_back(i + 1, count(adjacencyMatrix[i].begin(), adjacencyMatrix[i].end(), true));

    sort(indicesCounts.begin(), indicesCounts.end(),
         [](const auto& lhs, const auto& rhs) {return lhs.second > rhs.second;});

    // Revering the map (NT --> int) and getting sorted NTs
    map<int, string> index_NT;
    for (const auto& pair : NT_index)
        index_NT[pair.second] = pair.first;

    vector<string> sortedNTs;
    for(int i = 0; i < adjacencyMatrix.size(); i++) sortedNTs.push_back(index_NT[indicesCounts[i].first]);

    return sortedNTs;
}
