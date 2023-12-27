//
// Created by louay on 12/24/23.
//

#ifndef COMPILER_NTSORTER_H
#define COMPILER_NTSORTER_H

#include <bits/stdc++.h>
using namespace std;

class NTSorter {
    private:
        map<string, int> NT_index;
        vector<vector<bool>> adjacencyMatrix;

    public:
        NTSorter();
        NTSorter(map<string, vector<vector<string>>> rules);
        void applyFloydWarshall();
        vector<string> getNTSorted();
};


#endif //COMPILER_NTSORTER_H
