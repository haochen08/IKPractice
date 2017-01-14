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
#include <queue>
#include <stack>
#include "my_string.hpp"

using namespace std;

void LRU_cache::set(int key, int val)
{
    if (this->map.find(key) != this->map.end()) {
        this->elements.erase(this->map[key].second);
    }
    
    // This must be below the erase operation
    // Otherwise if we reset the existing key when cache is full,
    // it will wrongly evict the front element.
    if (this->elements.size() >= capacity) {
        this->evict();
    }
    
    this->elements.push_back(key);
    list<int>::iterator it = --this->elements.end();
    this->map[key] = {val, it};
}

int LRU_cache::get(int key)
{
    if (this->map.find(key) == this->map.end()) {
        return -1;
    }
    
    list<int>::iterator it = this->map[key].second;
    int val = this->map[key].first;
    this->elements.erase(it);
    this->elements.push_back(*it);
    this->map[key] = {val, --this->elements.end()};
    return val;
}

void LRU_cache::evict()
{
    if (!this->elements.empty()) {
        int key = this->elements.front();
        this->elements.pop_front();
        this->map.erase(this->map.find(key));
    }
}
// End of LRU_cache

void LFU_cache::set(int key, int val)
{
    if (lru_map.count(key)) {
        LRU_Node &rn = *lru_map[key];
        rn.val = val;
        return;
    }
    
    if (lru_map.size() >= capacity) {
        evict();
    }

    LRU_Node new_rn;
    new_rn.key = key;
    new_rn.val = val;
    new_rn.freq = 1;
    if (lfu_map.count(1)) {
        LFU_Node &fn = *lfu_map[1];
        fn.lru.push_back(new_rn);
        lru_map[key] = --fn.lru.end();
    } else {
        LFU_Node new_fn;
        new_fn.freq = 1;
        new_fn.lru.push_back(new_rn);
        lfu.push_front(new_fn);
        lru_map[key] = --lfu.front().lru.end();
        lfu_map[1] = lfu.begin();
    }

    min_freq = 1;
}

int LFU_cache::get(int key)
{
    if (!lru_map.count(key)) {
        return -1;
    }
    
    LRU_Node rn = *lru_map[key];
    LFU_Node &fn = *lfu_map[rn.freq];
    fn.lru.erase(lru_map[key]);
    lru_map.erase(key);
    rn.freq++;
    
    int new_freq = rn.freq;
    if (lfu_map.count(new_freq)) {
        LFU_Node &fn = *lfu_map[new_freq];
        fn.lru.push_back(rn);
        lru_map[key] = --fn.lru.end();
    } else {
        LFU_Node new_fn;
        new_fn.freq = new_freq;
        new_fn.lru.push_back(rn);
        auto it = lfu.insert(++lfu_map[rn.freq-1], new_fn);
        lfu_map[new_freq] = it;
        lru_map[key] = --(*it).lru.end();
    }
    
    if ((*lfu_map[min_freq]).lru.empty()) {
        min_freq++;
    }
    
    return rn.val;
}


void LFU_cache::evict()
{
    LFU_Node &fn = *lfu_map[min_freq];
    LRU_Node &rn = fn.lru.front();
    fn.lru.pop_front();
    lru_map.erase(rn.key);
}

// end of LFU_cache

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

void super_stack(vector<string> &ops)
{
    typedef pair<int, int> mypair;
    vector<mypair>  stack;
    string s;
    for (int i=0; i<ops.size(); i++) {
        vector<string> op;
        split_strings(ops[i], op, " ");
        if (op[0] == "push") {
            stack.push_back({stoi(op[1]), 0});
        } else if (op[0] == "pop") {
            if (!stack.empty()) {
                int size = stack.size();
                if (size > 1) {
                    stack[size-2].second += stack.back().second;
                }
                stack.pop_back();
            }
        } else {
            int index = stoi(op[1]);
            stack[index-1].second += stoi(op[2]);
        }
        
        if (stack.empty()) {
            cout << "EMPTY";
        } else {
            cout << stack.back().first + stack.back().second;
        }
    }
}

bool hasMatchingParantheses(std::string strExpression)
{
    stack<char> stack1;
    stack<char> stack2;
    stack<char> stack3;
    for (char c:strExpression) {
        switch (c) {
            case '{':
                stack1.push(c);
                break;
                
            case '}':
                if (stack1.empty()) {
                    return false;
                }
                stack1.pop();
                break;
                
            case '[':
                stack2.push(c);
                break;
                
            case ']':
                if (stack2.empty()) {
                    return false;
                }
                stack2.pop();
                break;
            case '(':
                stack3.push(c);
                break;
                
            case ')':
                if (stack3.empty()) {
                    return false;
                }
                stack3.pop();
                break;
                
            default:
                break;
        }
    }
    
    return true;
}

// The idea of the problem is
// 1. Use prev_start jumping the non-matching part.
// E.g. (()))((())), prev_start will jump to index 5
// 2. The current matching part start will be either the stack top if stack is not empty
// E.g. when idx is at 9, it will be 5
// or the prev_start -1 if it is empty
// E.g. when idx is at 10, it will be 4
// 3. [start, idx] is the current matching substring.
// Update the max if needed
int maxLenMatchingParen(string strParenExpression) {
    stack<int> stack;
    int max = 0;
    int prev_start = 0;
    for (int i=0; i<strParenExpression.length(); i++) {
        char c = strParenExpression[i];
        if (c == '(') {
            stack.push(i);
        } else {
            if (stack.empty()) {
                prev_start = i+1;
            } else {
                stack.pop();
                // if stack is empty, it is full match from prev_start
                // otherwise it is partial match
                auto start = stack.empty() ? prev_start - 1 : stack.top();
                auto size = i - start;
                if (size > max)
                {
                    max = size;
                }
            }
        }
    }
    
    return max;
}

void LRU_tests()
{
    cout << "LRU Tests ----" << endl;
    LRU_cache cache(2);
    cache.set(3, 1);
    cout << cache.get(3) << endl;
    cache.set(2, 2);
    cache.set(3, 3);
    cout << cache.get(3) << endl;
    cout << cache.get(2) << endl;
    cache.set(4, 4);
    cout << cache.get(2) << endl;
    cout << cache.get(3) << endl;
}

void LFU_tests()
{
    cout << "LFU Tests ----" << endl;
    LFU_cache cache(2);
    cache.set(1, 1);
    cache.set(2, 2);
    cout << cache.get(1) << endl;
    cache.set(3, 3);
    cout << cache.get(2) << endl;
    cout << cache.get(3) << endl;
    cache.set(4, 4);
    cout << cache.get(1) << endl;
    cout << cache.get(3) << endl;
    cout << cache.get(4) << endl;
}

void min_stack_tests()
{
    cout << "MinStack tests ----" << endl;
    MinStack ms;
    ms.push(1);
    ms.push(2);
    ms.push(-1);
    cout << ms.getMin() << endl;
    ms.pop();
    cout << ms.getMin() << endl;
    ms.pop();
    cout << ms.getMin() << endl;
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
    
    min_stack_tests();
    
    LRU_tests();
    LFU_tests();
}
