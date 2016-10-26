//
//  array_problem.hpp
//  Lesson-1
//
//  Created by Hao Chen on 9/16/16.
//  Copyright © 2016 HaoChen. All rights reserved.
//

#ifndef array_problem_hpp
#define array_problem_hpp

#include <sys/types.h>
#include <vector>
#include "sorting.hpp"

//--------------- 9/16/2016-----------------
// Problem
// Input: n size positive integer array
// Output Find the element which exists more than n/2
// If no, return -1
int find_majority(std::vector<uint> a);


// Problem
// Input: positive integer array within 1..n
// Output: Find the only dup
// If no, return -1
// TODO: How to find if any?
uint find_only_dup(std::vector<uint> a);

// Problem
// Input: positive integer array within 1..n
// Output: Find the only two dups
// TODO: How to find if any?
std::vector<uint> find_only_two_dups(std::vector<uint> a);

// Problem
// Input: n size integer
// where all integers exist in even times except two exist ONLY once
// Output: find these two
// TODO: How to find if any?
std::vector<int> find_two_only_exist(std::vector<int> a);


// Problem
// Input: positive integer array within 1..n
// Output: Find the only missing
// If no, return -1
// TODO: How to find if any?
uint find_only_missing(std::vector<uint> a);

//--------------9/17/2016--------------
// Problem
// Input: positive integer array within 1..2^32 with size of 4 x 10^9
// Ouput: find one missing
// Condition: memory is enough
int find_one_missing_in_4bil(std::vector<uint> a);

// Same to above but
// Condition: memory is not enough
int find_one_missing_in_4bil_mem_limited(std::vector<uint> a);

#endif /* array_problem_hpp */
