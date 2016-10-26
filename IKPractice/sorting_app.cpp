//
//  sorting_app.cpp
//  Lesson-1
//
//  Created by Hao Chen on 9/16/16.
//  Copyright © 2016 HaoChen. All rights reserved.
//

#include "sorting_app.hpp"
#include "sorting.hpp"
#include <string>

using namespace std;
vector<int> k_merge_sort(vector<vector<int>> &a, uint k)
{
    vector<heap_node> heap;
    for (uint i=0; i<k; i++) {
        heap_node node;
        node.x = i;
        node.y = 0;
        node.val = a[i][0];
        heap_insert(heap, node);
    }
    
    uint n = (uint)a[0].size();
    vector<int> sorted;
    sorted.reserve(n*k);
    for (uint i=0; i<n*k; i++)
    {
        heap_node root=heap[0];
        sorted.push_back(root.val);
        if (root.y+1 < n) {
            root.y = root.y+1;
            root.val = a[root.x][root.y];
        } else {
            root.val = INT_MAX;
        }
        heap[0] = root;
        heapifyDown(heap, 0, (int)heap.size());
    }
    
    return sorted;
}

string DutchFlagSort(string strColoredBalls) {
    int n=(int)strColoredBalls.length();
    int r=0, g=0, b=n-1;
    while (g <= b) {
        if (strColoredBalls[g] == 'R') {
            swap(strColoredBalls[g], strColoredBalls[r]);
            r += 1;
            g += 1;
        } else if (strColoredBalls[g] == 'G'){
            g = g+1;
        } else {
            swap(strColoredBalls[g], strColoredBalls[b]);
            b--;
        }
    }
    
    return strColoredBalls;
}
