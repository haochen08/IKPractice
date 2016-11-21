//
//  recursion.cpp
//  Lesson-1
//
//  Created by Hao Chen on 16/9/11.
//  Copyright © 2016年 HaoChen. All rights reserved.
//

#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include "recursion.hpp"

using namespace std;


bool isPuntuation(char c)
{
    return (c==',') || (c== '.');
}

bool isPalindrome(string s, int l, int r)
{
    if (l >= r) {
        return true;
    }
    
    if (isPuntuation(s[l])) {
        return isPalindrome(s, l+1, r);
    }
    
    if (isPuntuation(s[r])) {
        return isPalindrome(s, l, r-1);
    }
    
    if (s[l] != s[r]) {
        return false;
    }
    
    return isPalindrome(s, l+1, r-1);
}

bool isPalindrome(string s)
{
    return isPalindrome(s, 0, s.size()-1);
}

// T(n) = 2T(n-1)  T: O(2^n)
void subset(std::string &in, std::vector<char> &out, int read, int write)
{
    if (in.size() == read) {
        for (char c : out) {
            if (c != '\0')
                cout << c << ",";
        }
        cout << endl;
        return;
    }
    
    subset(in, out, read+1, write);
    out[write++] = in[read++];
    subset(in, out, read, write);
    out[write-1] = '\0';
}

void addingBrackets(string str, int n, int m){
    if(n==0 && m==0) {
        cout << str <<endl;
        return;
    }
    
    if (n > 0){
        addingBrackets(str+"(", n-1, m+1);
    }
    
    if (m > 0){
        addingBrackets(str+")", n, m-1);
    }

}

// n: remaining left brackets
// m: remaining right brackets
void addingBrackets2(string str, int n, int m){
    if(n==0 && m==0) {
        cout << str <<endl;
        return;
    }
    
    if (n > 0){
        addingBrackets2(str+"(", n-1, m);
    }
    
    if (n < m && m > 0){
        addingBrackets2(str+")", n, m-1);
    }
    
}

void addingBrackets3(string str, int n, int m, int size){
    if(n==size && m==size) {
        cout << str <<endl;
        return;
    }
    
    if (n < size){
        addingBrackets3(str+"(", n+1, m, size);
    }
    
    if (m < n){
        addingBrackets3(str+")", n, m+1, size);
    }
    
}

// T(n) = 2T(n-1)
// T: O(2^n)
void genBrackets(int n)
{
    string str;
    addingBrackets3(str, 0,0, n);
}

// T(n) = 2T(n-1)
// T: O(2^n)
int countTreesNum(int n)
{
    if (n == 0 || n == 1) {
        return 1;
    }
    
    int sum=0;
    for (int i=0; i<=n-1; i++) {
        int left = countTreesNum(i);
        int right = countTreesNum(n-1-i);
        sum += left*right;
    }
    
    return sum;
}

// T(n) = 2T(n-1)
// T: O(2^n)
bool groupSum(std::vector<int> &a, int i, int target)
{
    if (target == 0) {
        return true;
    }
    
    if (i == a.size()) {
        return false;
    }
    
    if (groupSum(a, i+1, target - a[i])) {
        cout << a[i] << ",";
        return true;
    }
    
    if (groupSum(a, i+1, target)) {
        return true;
    }
    
    return false;
}

bool hasLowerOrSamePrecedence(char op1, char op2)
{
    if (op1 == '"') {
        return false;
    }
    
    if (op1 == '*' && op2 == '+') {
        return false;
    }
    
    return true;
}

int applyOp(char op, int a, int b)
{
    switch (op) {
        case '+':
            return a+b;
        case '*':
            return a*b;
        case '"':
            string s;
            s += to_string(a) + to_string(b);
            return stoi(s);
    }
    
    return 0;
}

bool evaluate(std::vector<char> &exp, int target)
{
    stack<char> ops;
    stack<int> values;
    for (char c:exp) {
        if (c >= '0' && c <= '9') {
            values.push(char(c)-48);
        } else {
            while (!ops.empty() && hasLowerOrSamePrecedence(c, ops.top())) {
                char topOp = ops.top();
                int opr1 = values.top();
                values.pop();
                int opr2 = values.top();
                values.pop();
                values.push(applyOp(topOp, opr2, opr1));
                ops.pop();
            }
            
            ops.push(c);
        }
    }
    
    while (!ops.empty()) {
        char topOp = ops.top();
        char opr1 = values.top();
        values.pop();
        char opr2 = values.top();
        values.pop();
        values.push(applyOp(topOp, opr2, opr1));
        ops.pop();
    }
    
    int val = values.top();
    return val == target;

}

void addOperators(std::string &a, std::vector<char> &exp, int i, int target)
{
    if (a.length() == 1) {
        if (stoi(a) == target)
            cout << a << "=" << target << endl;
        return;
    }
    
    if (i >= a.length()) {
        bool b = evaluate(exp, target);
        if (b) {
            for (char c:exp) {
                cout << c;
            }
            cout << "=" << target << endl;
        }
        
        return;
    }
    
    if (i == 0) {
        exp.push_back(a[i]);
        addOperators(a, exp, 1, target);
        return;
    }
    
    int size = exp.size();
    exp.push_back('+');
    exp.push_back(a[i]);
    addOperators(a, exp, i+1, target);
    exp.resize(size);
    
    exp.push_back('*');
    exp.push_back(a[i]);
    addOperators(a, exp, i+1, target);
    exp.resize(size);
    
    exp.push_back('"');
    exp.push_back(a[i]);
    addOperators(a, exp, i+1, target);
    exp.resize(size);
}

// T: O(n!)
void palindromeDecompRecur(std::string &a, int i, vector<string> &res)
{
    if (i == a.size()) {
        for (string str:res) {
            cout << str << "|";
        }
        cout << endl;
        
        return;
    }
    
    for (int j=i+1; j<=a.size(); j++) {
        string cur = a.substr(i,j-i);
        if (isPalindrome(cur)) {
            res.push_back(cur);
            palindromeDecompRecur(a, j, res);
            res.pop_back();
        }
    }
}

void palindromeDecomp(std::string &a)
{
    vector<string> s;
    palindromeDecompRecur(a, 0, s);
}

// T(n) = T(n/2)
// T: O(logn)
float pow(float dblbase, float result, int ipower, bool sign)
{
    if (ipower == 0) {
        if (sign) {
            return result;
        } else {
            return 1.0 / result;
        }
    }
    
    if (ipower & 1) {
        result *= dblbase;
    }
    
    return pow(dblbase*dblbase, result, ipower / 2, sign);
}

float pow(float dblbase, int ipower)
{
    return pow(dblbase, 1, ipower, ipower > 0);
}

void printQueenSolution(int a[], int N)
{
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << "+-";
        }
        cout << "+" << endl;
        for (int j = 0; j < N; j++) {
            if (a[i] == j) {
                cout << "|*";
            } else {
                cout << "| ";
            }
        }
        cout << "|" << endl;
    }
    
    for (int j = 0; j < N; j++) {
        cout << "+-";
    }
    cout << "+" <<endl;
}

//T(n) = nT(n-1)
// T: n!
void permutation_recur(int a[], int N, int level)
{
    if (level == N) {
        for (int i=0; i<N; i++) {
            cout << a[i] << " ";
        }
        cout << endl;
        return;
    }
    
    for (int i = level; i < N; i++) {
        swap(a[level], a[i]);
        permutation_recur(a, N, level+1);
        swap(a[level], a[i]);
    }
}

bool valid(int a[], int N)
{
    for (int i=0; i<N-1; i++) {
        for (int j=i+1; j<N; j++) {
            if (abs(a[j]-a[i]) == (j-i)) {
                return false;
            }
        }
    }
    
    return true;
}

void NQueen_recur(int a[], int N, int level)
{
    if (level == N) {
        if (valid(a, N)) {
            printQueenSolution(a, N);
            cout << endl;
        }

        return;
    }
    
    for (int i = level; i < N; i++) {
        swap(a[level], a[i]);
        NQueen_recur(a, N, level+1);
        swap(a[level], a[i]);
    }
}

void permutation(int N)
{
    int a[N];
    for (int i = 0; i < N; i++) {
        a[i] = i;
    }
    
    permutation_recur(a, N, 0);
}

void NQueen(int N)
{
    int a[N];
    for (int i = 0; i < N; i++) {
        a[i] = i;
    }
    
    NQueen_recur(a, N, 0);
}













