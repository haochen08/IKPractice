//
//  ad_hoc.cpp
//  Lesson-1
//
//  Created by Hao Chen on 10/23/16.
//  Copyright © 2016 HaoChen. All rights reserved.
//

#include "ad_hoc.hpp"
#include <queue>
#include <iostream>
#include <vector>
#include "my_string.hpp"

using namespace std;

void shuffle_array_in_equally_likely(int a[], int m)
{
    
}


std::vector<int> sliding_window_max(const std::vector<int> &a, int k)
{
    std::vector<int> window_max;
    deque<int> promising;
    // Each element in array is checked once which yields O(n) complexity
    for (int i=0; i<a.size(); i++) {
        // This ensures to pop the front which is out of scope
        if (!promising.empty() && promising.front() < i-k+1) {
            promising.pop_front();
        }
        
        // This guarantees the front will always be the maximum
        while (!promising.empty() && a[promising.back()] < a[i]) {
            promising.pop_back();
        }
        
        promising.push_back(i);
        if (i >= k-1) {
            window_max.push_back(a[promising.front()]);
        }
    }
    
    return window_max;
}

void super_stack()
{
    vector<int>  stack;
    vector<string> output;
    string s;
    getline(cin, s);
    int size = stoi(s);
    for (int i=0; i<size; i++) {
        getline(cin, s);
        vector<string> ops;
        split_strings(s, ops, " ");
        if (ops[0] == "push") {
            stack.push_back(stoi(ops[1]));
        } else if (ops[0] == "pop") {
            if (!stack.empty()) {
                stack.pop_back();
            }
        } else {
            // unnecessary to do all
            for (int i=0; i<stoi(ops[1]); i++) {
                stack[i] += stoi(ops[2]);
            }
        }
        
        if (stack.empty()) {
            output.push_back("EMPTY");
        } else {
            output.push_back(to_string(stack.back()));
        }
    }
    
    for (string line:output) {
        cout << line << endl;
    }
}

void ad_hoc_tests()
{
    vector<int> a = {-3,1,-2,3,1,5};
    vector<int> res = sliding_window_max(a, 3);
    cout << "sliding_window_max--- ";
    for (auto i:res) {
        cout << i << " ";
    }
    cout << endl;
    
    super_stack();
}
