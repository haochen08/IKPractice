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

void ad_hoc_tests()
{
    vector<int> a = {-3,1,-2,3,1,5};
    vector<int> res = sliding_window_max(a, 3);
    cout << "sliding_window_max--- ";
    for (auto i:res) {
        cout << i << " ";
    }
    cout << endl;
}
