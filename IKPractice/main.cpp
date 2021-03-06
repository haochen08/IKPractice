//
//  main.cpp
//  Lesson-1
//
//  Created by Hao Chen on 8/28/16.
//  Copyright © 2016 HaoChen. All rights reserved.
//

#include <vector>
#include <stack>
#include <iostream>

#include "sorting.hpp"
#include "sorting_app.hpp"
#include "recursion.hpp"
#include "array_problem.hpp"
#include "tree.hpp"
#include "dp.hpp"
#include "linked_list.hpp"
#include "my_string.hpp"
#include "graph.hpp"
#include "ad_hoc.hpp"


using namespace std;
void print_array_element(vector<int> &elements)
{
    for (int item: elements) {
        cout << item << " ";
    }
    cout << endl;
}

void print_points_array(vector<point> &elements)
{
    for (point pt: elements) {
        cout << pt.x << "," << pt.y << " ";
    }
    cout << endl;
}

void map_string_test(string &s)
{
    vector<uint> buckets;
    buckets.reserve(256); // ASCII
    for (char item:s)
    {
        buckets[item]++;
    }
    
    uint k = 0;
    for (uint i=0; i<256; i++)
    {
        for (uint j=0; j<buckets[i]; j++) {
            s[k++] = i;
        }
    }
}



int findDuplicateFromPermutation(vector < int > intArray) {
    uint len = intArray.size();
    int buckets[len];
    memset(buckets, 0, sizeof(int)*len);
    for (uint i:intArray) {
        buckets[i-1]++;
    }
    
    for (uint i=0; i<len; i++) {
        if (buckets[i] > 1) {
            return i+1;
        }
    }
    
    return -1;
}

void print_permutation(vector<int> set, uint i)
{
    if (i == set.size()-1) {
        print_array_element(set);
        return;
    }
    
    for (uint j=i; j<set.size(); j++) {
        // ? When j==i, it will swap itself. Is this necessary?  
        swap(set[i],set[j]);
        print_permutation(set, i+1);
        swap(set[i],set[j]);
    }
}

vector < int > topK(vector < int > iStream, int iK) {
    vector<int> heap,res;
    for (int i:iStream) {
        heap_insert(heap, i);
    }
    
    for (uint i=0; i<iK; i++) {
        res.push_back(heap[0]);
        swap(heap[0], heap[heap.size()-i-1]);
        heapifyDown(heap, 0, heap.size()-i-1);
    }
    
    return res;
}

vector<int> topK2(vector<int> iStream, int iK) {
    return quick_sort_k(iStream, 0, (uint)iStream.size()-1, iK);
}


void sorting_test() {
    vector<vector<int>> a = {{1,3,5,7}, {2,4,5,8}, {3,4,5,6}};
    vector<int> result = k_merge_sort(a, 3);
    print_array_element(result);
}

void hanoi(int n, int source, int target, int middle) {
    if (n == 0)
        return;
    hanoi(n-1, source, middle, target);
    cout << source << " -> " << target << endl;
    hanoi(n-1, middle, target, source);
    
}


int main(int argc, const char * argv[]) {
    graph_test();

    return 0;
}
