//
//  ad_hoc.hpp
//  Lesson-1
//
//  Created by Hao Chen on 10/23/16.
//  Copyright © 2016 HaoChen. All rights reserved.
//

#ifndef ad_hoc_hpp
#define ad_hoc_hpp

#include <stdio.h>
#include <vector>
#include <string>
#include <unordered_map>
#include <list>
#include <tuple>
#include <stack>

class LRU_cache
{
public:
    int capacity;
    LRU_cache(int _capacity):capacity(_capacity) {}
    void set(int key, int val);
    int get(int key);
private:
    typedef std::pair<int, std::list<int>::iterator> my_pair; // pair <val, it to elements node>
    std::unordered_map<int, my_pair> map;
    std::list<int>   elements;
    void evict();
};

class LFU_cache
{
    struct LRU_Node {
        int key, val, freq;
    };
    
    struct LFU_Node {
        int freq;
        std::list<LRU_Node> lru;
    };
    
public:
    LFU_cache(int _capacity):capacity(_capacity){}
    void set(int key, int val);
    int get(int key);
private:
    std::unordered_map<int, std::list<LFU_Node>::iterator> lfu_map;  // freq -> iter of lfu
    std::unordered_map<int, std::list<LRU_Node>::iterator> lru_map;   // key -> iter in lru
    std::list<LFU_Node> lfu;
    int capacity;
    int min_freq;

    void evict();
};

// Idea is to use two stack
// Push to stack b if the value to push is less or equal(for dup value) then current min
// This will ensure the top of b will always return the current min value.
class MinStack
{
private:
    std::stack<int> a, b;
    
public:
    void push(int i)
    {
        // 1. The former condition is for the first time.
        // This helps to introduce extra min value
        // 2. <= is necessary for dup value
        if (b.empty() || i <= getMin()) {
            b.push(i);
        }
        
        a.push(i);
    };
    
    void pop()
    {
        if (a.top() == b.top()) {
            b.pop();
        }
        a.pop();
    }
    
    int top()
    {
        return a.top();
    }
    
    int getMin()
    {
        return b.top();
    }
    

};

// Given the array, shuffle the array so that every element is with equally likely
// ? Random generator
// Brutal
// 1. Generate all perm
// 2. User random generator [0..N!] to get the index
// T: N!
// S: N*N!
void shuffle_array_in_equally_likely(int a[], int m);

std::vector<int> sliding_window_max(const std::vector<int> &a, int k);
void super_stack(std::vector<std::string> & str);
bool hasMatchingParantheses(std::string strExpression);

// Longest substring with matching parantheses
int maxLenMatchingParen(std::string strParenExpression);
void ad_hoc_tests();
#endif /* ad_hoc_hpp */
