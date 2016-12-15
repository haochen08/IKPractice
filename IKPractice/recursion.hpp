//
//  recursion.hpp
//  Lesson-1
//
//  Created by Hao Chen on 16/9/11.
//  Copyright © 2016年 HaoChen. All rights reserved.
//

#ifndef recursion_hpp
#define recursion_hpp

#include <string>


// How to analyze the time complexiy of recursion problem
// 1. T(n) = T(n/2)
// O(logn)
// e.g. Binary search, heap_siftDown
// 2. T(n) = T(n-1)
// O(n)
// e.g. Reverse linked list, Factor(n), build_heap...
// 3. T(n) = 2T(n/2)
// O(nlogn)
// e.g. Quick sort
// 4. T(n) = kT(n-1)
// O(k^n)
// e.g. generateParenthese, subset  
// 5. T(n) = nT(n-1)
// O(n!)
// e.g. Permutation

bool isPalindrome(std::string s);

//--------------- 9/22/2016-----------------
// Problem
// Input: Set
// Output: All subset
void subset(std::string &in, std::vector<char> &out, int read, int write);
std::vector<std::vector<int>> subsetsWithDup(std::vector<int>& nums);

// Problem
// Input: count of tree nodes
// Output: count of trees number
int countTreesNum(int n);

// -------------9/26/2016------
void genBrackets(int n);


// Problem
// Input:
// a: array with  integer
// target: target number
// Output:
// Return if sum of any elements equals to target
bool groupSum(std::vector<int> &a, int i, int target);

// leetcode39
// Given an array with all unique positive integers and a target,
// return all the unique combinations which sums to target.
// Each element can be used in unlimited times.
std::vector<std::vector<int>> combinationSum1(std::vector<int>& candidates, int target);
// leetcode40
// Given an array with all positive integers (which could contain duplicates) and a target,
// return all the unique combinations which sums to target.
// Each element can be used only once.
// @similar subset dups
std::vector<std::vector<int>> combinationSum2(std::vector<int>& candidates, int target);
// leetcode 219
// Digit set {1..9}, choose k of them, return all unique combinations summing to n
// Each element can be used only once.
// @similar kSum, binary watch
std::vector<std::vector<int>> combinationSum3(int k, int n);

// Problem
// Input
// a: digits in string e.g. "123434'
// exp: operators in string "+ * '"
// Target: target number
//
// Output
// Return if it can reach target by insert operator in between the digits
void addOperators(std::string &a, std::vector<char> &exp, int i, int target);

// Palindrome Decomposition
void palindromeDecomp(std::string &a);

// Raise a double to an int power including negative powers
float pow(float dblbase, int ipower);

void permutation(int N);

// output perm from a seq which may contain dup e.g. {1,1,2}
std::vector<std::vector<int>> permutationOnDup(std::vector<int> &nums);

bool binarySearch(std::vector<int> a, int x);

// find if x exists in pivot rotate sorted array like {3,4,5,1,2} pivot = 5
bool rotatedBinarySearch(std::vector<int> a, int x);
bool rotatedBinarySearch2(std::vector<int> a, int x, int low, int high);

// find min in rotate sorted array like {3,4,5,1,2} pivot = 5 which is 1
int minInRotatedSortArray(std::vector<int> a);

// print solutions count for NQueen
int NQueen(int N);

// Binary Watch leetcode 401
std::vector<std::string> readBinaryWatch(int num);

// Generate all Palindromes in Permutation
std::vector<std::string> generatePalindromes(std::string s);

int find_max_path_recur(std::vector<std::vector<int>> &a, int i, int j);

int find_min_path_in_triangle_recur(std::vector<std::vector<int>> &a, int i, int j);

int min_edit_dist_between_str(std::string &st, std::string &ed, int p1, int p2, int st_len);

void recursive_tests();

#endif /* recursion_hpp */
