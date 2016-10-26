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

bool isPalindrome(std::string s);

//--------------- 9/22/2016-----------------
// Problem
// Input: Set
// Output: All subset
void subset(std::string &in, std::vector<char> &out, int read, int write);

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
void groupSum2(std::vector<int> &a, int i, int target);

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

void printNQueen(int N);
#endif /* recursion_hpp */
