//
//  array_problem.cpp
//  Lesson-1
//
//  Created by Hao Chen on 9/16/16.
//  Copyright © 2016 HaoChen. All rights reserved.
//

#include <bitset>
#include "array_problem.hpp"

using namespace std;

int find_majority(std::vector<uint> a)
{
    int winner = -1;
    uint cnt = 0;
    for (uint item:a) {
        if (cnt == 0) {
            winner = item;
            cnt = 1;
        } else if (item != winner) {
            cnt--;
            if (cnt == 0) {
                winner = -1;
            }
        } else {
            cnt++;
        }
    }
    
    if (winner == -1) {
        return -1;
    }
    
    if (cnt > a.size()/2) {
        return winner;
    }
    
    cnt = 0;
    for (uint item:a) {
        if (item == winner) {
            cnt++;
        }
    }
    
    if (cnt > a.size() /2) {
        return winner;
    }
    
    return -1;
}

uint find_only_dup(std::vector<uint> a)
{
    auto n = a.size()-1;
    uint xr = 0;
    for (uint i=1; i<=n; i++) {
        xr ^= i;
    }
    
    for (uint e:a) {
        xr ^= e;
    }
    
    return xr;
}

vector<uint> find_only_two_dups(vector<uint> a)
{
    auto n = a.size()-2;
    int xr = 0;
    for (uint i=1; i<=n; i++) {
        xr ^= i;
    }
    
    for (uint e:a) {
        xr ^= e;
    }
    
    int set_bit = xr & (-xr);
    uint x=0, y=0;
    for (uint e:a) {
        if (set_bit & e) {
            x ^= e;
        } else {
            y ^= e;
        }
    }
    
    for (uint i=1; i<=n; i++) {
        if (set_bit & i) {
            x ^= i;
        } else {
            y ^= i;
        }
    }
    
    return {x,y};
}

std::vector<int> find_two_only_exist(std::vector<int> a)
{
    int xr = 0;
    for (int e:a) {
        xr ^= e;
    }
    
    int set_bit = xr & (-xr);
    int x=0, y=0;
    for (int e:a) {
        if (e & set_bit) {
            x ^= e;
        } else {
            y ^= e;
        }
    }
    
    return {x,y};
}

uint find_only_missing(std::vector<uint> a)
{
    auto n = a.size()+1;
    uint xr = 0;
    for (uint e: a) {
        xr ^= e;
    }
    
    for (uint i=1; i<=n; i++) {
        xr ^= i;
    }
    
    return xr;
}

int find_one_missing_in_4bil(std::vector<uint> a)
{
    uint bit_len = 32;
    vector<bitset<32>>  bitmap;
    // 0xFFFFFFFF is UINT32_MAX;
    uint map_size = 0xFFFFFFFF / bit_len;
    bitmap.reserve(map_size);
    for (uint e:a) {
        // TODO Why bitmap[e/bit_len] works under reserve instead of bitmap.pushback(..)?
        bitmap[e/bit_len].set(e%bit_len);
    }
    
    for (uint j=0; j<map_size; j++) {
        for (uint i=0; i<bit_len; i++) {
            if (!bitmap[j].test(i)) {
                return j*bit_len+i;
            }
        }
    }
    
    return -1;
}

int find_one_missing_in_4bil_mem_limited_recursive(std::vector<uint> a, uint bit, bitset<4> bitmap) {
    uint bit_len = 4;
    if (bit == bit_len) {
        return (int)bitmap.to_ulong();
    }
    
    // Using two vectors to simulate two files
    uint mask = 1<<(bit_len-1-bit);
    vector<uint> ones, zeros;
    for (uint e:a) {
        if (mask & e) {
            // Use push_back to vector to simulate writing to file
            ones.push_back(e);
        } else {
            zeros.push_back(e);
        }
    }
    
    if (zeros.size() < mask) {
        return find_one_missing_in_4bil_mem_limited_recursive(zeros, bit+1, bitmap);
    }
    
    bitmap.set(bit_len-1-bit);
    return find_one_missing_in_4bil_mem_limited_recursive(ones, bit+1, bitmap);
}

int find_one_missing_in_4bil_mem_limited(std::vector<uint> a)
{
    bitset<4> bitmap;
    return find_one_missing_in_4bil_mem_limited_recursive(a, 0, bitmap);
}










