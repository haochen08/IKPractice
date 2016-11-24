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

// Note here it is pass by value for seq
void permutation_dup_recur(vector<int> seq, int level, vector<vector<int>> & output)
{
    if (level == seq.size()) {
        output.push_back(seq);
        return;
    }
    
    for (int i=level; i<seq.size(); i++) {
        // skip dup
        if (i != level && seq[i] == seq[level])
            continue;
        
        swap(seq[i], seq[level]);
        permutation_dup_recur(seq, level+1, output);
        // No swap back since we want to maintain the subseq [level+1, n-1] is still sorted
        // Otherwise we can will have a same subset as before.
        // Example is 1 2 2 3
        // when swap (level=0, i=1)
        // it is 2 1 2 3
        // If we swap back and process (level=0, i=2)
        // it is 2 2 1 3.
        // Then the subset [1,2,3] is the same as [2,1,3].
        // which will yield a dup output
        // However if we don't swap back, it will skip since seq[level=0] == seq[i=2] = 2
        // Meanwhile since we can't swap back, we have to use pass by value
        
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

bool canPlace(int a[], int col)
{
    for (int i=0; i<col; i++) {
        if (abs(a[col]-a[i]) == (col-i)) {
            return false;
        }
    }
    
    return true;
}

void NQueen_recur(int a[], int N, int level, int &sol_num)
{
    if (level == N) {
        //printQueenSolution(a, N);
        //cout << endl;
        sol_num++;
        return;
    }
    
    for (int i = level; i < N; i++) {
        swap(a[level], a[i]);
        if (canPlace(a, level)) {
            NQueen_recur(a, N, level+1, sol_num);
        }
        
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



std::vector<std::vector<int>> permutationOnDup(std::vector<int> &nums)
{
    vector<vector<int>> output;
    // sort is necessary to skip dup
    sort(nums.begin(), nums.end());
    permutation_dup_recur(nums, 0, output);
    return output;
}

int NQueen(int N)
{
    int a[N], sol_num=0;
    for (int i = 0; i < N; i++) {
        a[i] = i;
    }
    
    NQueen_recur(a, N, 0, sol_num);
    return sol_num;
}

bool binarySearchRecur(vector<int> a, int x, int st, int ed)
{
    if (st > ed) {
        return false;
    }
    
    int mid = st+(ed-st)/2;
    if (x == a[mid]) {
        return true;
    }
    
    if (x > a[mid]) {
        return binarySearchRecur(a, x, mid+1, ed);
    } else {
        return binarySearchRecur(a, x, st, mid-1);
    }
}

bool binarySearch(vector<int> a, int x)
{
    return binarySearchRecur(a, x, 0, (int)a.size()-1);
}

int findPivot(vector<int> a, int st, int ed)
{
    // If cross, means there is not any pivot
    if (st > ed) {
        return -1;
    }
    
    int mid = st+(ed-st)/2;
    // solve for duplicate
    // Note we should decrement from ed instead of st
    // Think about 3 1 3 3 3. If we decrement from st, then we'll miss the pivot 3.
    if (mid < ed && a[mid] == a[ed]) {
        return findPivot(a, st, ed-1);
    }
    
    // if pivot is among mid, mid-1 and mid+1, just return
    if (mid > st && a[mid] < a[mid-1]) {
        return mid-1;
    }
    
    if (mid < ed && a[mid] > a[mid+1]) {
        return mid;
    }
    
    // Otherwise divide and conquer
    if (a[mid] < a[ed]) {
        return findPivot(a, st, mid-1);
    }
    
    return findPivot(a, mid+1, ed);
}
bool rotatedBinarySearch(vector<int> a, int x)
{
    int id = findPivot(a, 0, a.size()-1);
    if (id == -1) {
        return binarySearchRecur(a, x, 0, (int)a.size()-1);
    }
    
    if (x == a[id]) {
        return true;
    }
    
    if (x > a[0]) {
        return binarySearchRecur(a, x, 0, id-1);
    }
    
    return binarySearchRecur(a, x, id+1, a.size()-1);
}

bool rotatedBinarySearch2(vector<int> a, int x, int low, int high)
{
    if (low > high) {
        return false;
    }
    
    int mid = low + (high-low)/2;
    if (x == a[mid]) {
        return true;
    }
    
    // a[mid] == a[low] if there is dup
    // like 1 3 1 1 1, 1 1 1 3 1 (x = 3)
    // we can only shrink by one from low
    if (a[mid] == a[low]) {
        return rotatedBinarySearch2(a, x, low+1, high);
    }
    
    if (a[mid] > a[low]) {
        if (x >= a[low] && x < a[mid]) {
            return rotatedBinarySearch2(a, x, low, mid-1);
        }
        
        return rotatedBinarySearch2(a, x, mid+1, high);
    }
    
    if (x > a[mid] && x <= a[high]) {
        return rotatedBinarySearch2(a, x, mid+1, high);
    }
    
    return rotatedBinarySearch2(a, x, low, mid-1);
}

int minInRotatedSortArray(std::vector<int> a)
{
    int id = findPivot(a, 0, a.size()-1);
    if (id == -1) {
        return a[0];
    }
    
    return a[id+1];
}












