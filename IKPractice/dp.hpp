//
//  dp.hpp
//  Lesson-1
//
//  Created by Hao Chen on 16/10/8.
//  Copyright © 2016年 HaoChen. All rights reserved.
//

#ifndef dp_hpp
#define dp_hpp

#include <stdio.h>
#include <vector>

// Problem
// Coinchange
// Input: amount of money, denominator
// Output: minimum change from denominator
int coinchange(int amount, std::vector<int> &denom);

// Problem
// Find a path from topleft to bottomright on matrix
// to maximize the sum of weight
int find_max_path(std::vector<std::vector<int>> x);

// Problem
// Longest Increasing Sequence
int find_lis(std::vector<int> seq);

// Problem
// Maxium Product Cutting
int maxProductFromCutPieces(int n);

// Problem
// Number of path in [0,1] matrix
// http://www.geeksforgeeks.org/count-possible-paths-top-left-bottom-right-nxm-matrix/
int numberOfPaths(std::vector<std::vector<int>> matrix);

int maximumSubSeq(std::string str1, std::string str2);

int find_min_path_in_triangle(std::vector<std::vector<int>> &a);

void dp_tests();


#endif /* dp_hpp */
