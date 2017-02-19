//
//  dp.cpp
//  Lesson-1
//
//  Created by Hao Chen on 16/10/8.
//  Copyright © 2016年 HaoChen. All rights reserved.
//

#include <iostream>
#include <vector>
#include <stack>
#include <set>
#include <unordered_map>
#include "dp.hpp"

using namespace std;

int coinchangecount(int amount, vector<int> &denom)
{
    auto M = amount+1;
    int count[M];
    memset(count, 0, sizeof(int)*M);
    count[0] = 1;
    // Should interate the coins first, why?
    for (int d:denom) {
        for (int i=1; i<=amount; i++) {
            if (i >= d) {
                count[i] += count[i-d];
            }
        }
    }

    return count[M-1];
}

// f(i) = min(f(i-d(j))+1, f(i)) 0<=j<n (n coins)
int coinchange2(int amount, std::vector<int> &denom)
{
    vector<int> dp, tp;

    tp.resize(amount+1);
    dp.resize(amount+1);
    for (int i=0; i<dp.size(); i++) {
        if (i == 0) {
            dp[i] = 0;
        } else {
            dp[i] = INT_MAX-1;
        }

        tp[i] = -1;
    }

    for (int d:denom) {
        for (int a=1; a<=amount; a++) {
            if (a>=d) {
                int temp = dp[a-d]+1;
                if (temp <= dp[a]) {
                    dp[a] = temp+1;
                    tp[a] = d;
                }
            }
        }
    }
    
    if (dp[amount] == INT_MAX-1) {
        return -1;
    }
    
    int st = amount;
    while (st > 0) {
        cout << tp[st] << " ";
        st -= tp[st];
    }

    return dp[amount];
}

int coinchange(int amount, std::vector<int> &denom)
{
    vector<int> cache;
    // 1. Note the size is amount+1, not amount.
    cache.resize(amount+1);
    
    for (int a=0; a<=amount; a++) {
        if (a == 0) {
            cache[a] = 0;
        } else {
            int min = INT_MAX-1;
            int ans;
            for (int d:denom) {
                if (a >= d) {
                    ans = cache[a-d];
                    if (ans+1 < min) {
                        min = ans+1;
                    }
                }
            }
            
            cache[a] = min;
        }
    }
    
    // Print the solution
    if (cache[amount] > 0) {
        int a = amount;
        while (a > 0)
        {
            int min = INT_MAX;
            int min_d = 0;
            for (int i=0; i<denom.size(); i++)
            {
                if (a<denom[i]) {
                    continue;
                }
                
                if (cache[a-denom[i]] < min) {
                    min_d = i;
                    min = cache[a-denom[i]];
                }
            }
            
            cout << denom[min_d] << ",";
            a -= denom[min_d];
            
        }
        
        cout << endl;
    }
    
    return cache[amount];
}

// Rely dp to be initialized before calling
int find_max_path_top_down(std::vector<std::vector<int>> &A, int dp[][4], int i, int j)
{
    int M = A.size(), N = A[0].size();
    if (i == 0 && j == 0) {
        dp[i][j] = A[i][j];
        return dp[i][j];
    }
    
    if (dp[i][j] <= 0) {
        int max_val = INT_MIN;
        if (i == 0) {
            dp[i][j] = find_max_path_top_down(A, dp, i, j-1) + A[i][j];
            cout << "(" << i << "," << j-1 << ")"<< endl;
        } else if (j == 0) {
            dp[i][j] = find_max_path_top_down(A, dp, i-1, j) + A[i][j];
            cout << "(" << i-1 << "," << j << ")"<< endl;
        } else {
            int tp1 = find_max_path_top_down(A, dp, i, j-1);
            int tp2 = find_max_path_top_down(A, dp, i-1, j);
            if (tp1 > tp2) {
                dp[i][j] = tp1 + A[i][j];
                cout << "(" << i << "," << j-1 << ")"<< endl;
            } else {
                dp[i][j] = tp2 + A[i][j];
                cout << "(" << i-1 << "," << j << ")"<< endl;
            }
        }
    }
    
    return dp[i][j];
}

int find_max_path(std::vector<std::vector<int>> x)
{
    int M = x.size(), N = x[0].size();
    int cache[M][N];
    memset(cache, 0, sizeof(int)*M*N);
    for (int i=M-1; i>=0; i--) {
        for (int j=N-1; j>=0; j--) {
            if (i == M-1 && j == N-1) {
                cache[i][j] = x[i][j];
            } else if (i == M-1) {
                cache[i][j] = x[i][j] + cache[i][j+1];
            } else if (j == N-1) {
                cache[i][j] = x[i][j] + cache[i+1][j];
            } else {
                int down = x[i][j] + cache[i][j+1];
                int right = x[i][j] + cache[i+1][j];
                cache[i][j] = max(down, right);
            }
        }
    }
    
    // print path
    int i=0,j=0,sum=cache[0][0];
    cout <<"0,0" << endl;
    while (true) {
        if (i == M-1 && j == N-1) {
            break;
        } else if (i == M-1){
            j++;
        } else if (j == N-1) {
            i++;
        } else {
            sum -= x[i][j];
            if (sum == cache[i+1][j]) {
                i++;
            } else {
                j++;
            }
        }
        
        cout << i << "," << j << endl;
        
    }

    return cache[0][0];
}

int find_lis(vector<int> seq)
{
    int n = seq.size()-1;
    vector<int> dp;
    dp.resize(n);
    for (int i=n-1; i>=0; i--) {
        if (i == n-1) {
            dp[i] = 1;
        } else {
            int max = INT_MIN;
            for (int j = i+1; j<n; j++) {
                if (dp[j] > max && seq[i] < seq[j]) {
                    max = dp[j];
                }
            }
            
            if (max == INT_MIN) {
                dp[i] = 1;
            } else {
                dp[i] = max+1;
            }
        }
    }
    
    int max = INT_MIN;
    for (int i:dp) {
        if (i > max) {
            max = i;
        }
    }
    
    return max;
}

int maxProductFromCutPieces(int ropelength) {
    int val[ropelength+1];
    val[0] = val[1] = 0;
    
    for (int i = 2; i <= ropelength; i++)
    {
        int max_val = INT_MIN;
        // Notice the loop end is i/2 instead of i-1
        for (int j = 1; j <= i/2; j++) {
            if ((i-j)*j > max_val) {
                max_val = (i-j)*j;
            }
            
            if (j*val[i-j] > max_val) {
                max_val = j*val[i-j];
            }
        }
        val[i] = max_val;
    }
    
    return val[ropelength];
}

int numberOfPaths(vector<vector<int>> matrix)
{
    int m = matrix.size();
    int n = matrix[0].size();
    // Create a 2D table to store results of subproblems
    int count[m][n];
    
    count[0][0] = matrix[0][0];
    for (int i = 1; i < m; i++)
        count[i][0] = matrix[i][0] * count[i-1][0];
    
    for (int j = 1; j < n; j++)
        count[0][j] = matrix[0][j] * count[0][j-1];

    for (int i = 1; i < m; i++)
    {
        for (int j = 1; j < n; j++) {
            if (matrix[i][j] == 0) {
                count[i][j] = 0;
            } else {
                count[i][j] = count[i-1][j] + count[i][j-1];
            }
        }
    }
    
    return count[m-1][n-1];
}

int find_min_path_in_triangle(std::vector<std::vector<int>> &a)
{
    int M = a.size();
    int cache[M][M];
    memset(cache, 0, sizeof(int)*M*M);
    for (int i=M-1; i>=0; i--) {
        for (int j=0; j<=i; j++) {
            if (i == M-1) {
                cache[i][j] = a[i][j];
            } else {
                cache[i][j] = min(cache[i+1][j], cache[i+1][j+1]) + a[i][j];
            }
        }
    }
    
    return cache[0][0];
}

string longestCommonSeq(std::string & str1, std::string & str2)
{
    int M = str1.length()+1, N = str2.length()+1;
    int dp[M][N];
    memset(dp, 0, sizeof(int)*M*N);
    for (int i=1; i<M; i++) {
        for (int j=1; j<N; j++) {
            if (str1[i-1] == str2[j-1]) {
                dp[i][j] = dp[i-1][j-1]+1;
            } else {
                dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
            }
        }
    }
    
    int i=M-1, j=N-1;
    string str;
    while (true) {
        if (i==0 || j == 0) {
            break;
        } else if (dp[i][j] == (dp[i-1][j-1]+1)){
            str += str1[i-1];
            i--;
            j--;
        } else if (dp[i][j] == dp[i-1][j]) {
            i--;
        } else {
            j--;
        }
    }
    
    reverse(str.begin(), str.end());
    return str;
}

// Pattern can have '.' '*'
bool regexMatch(std::string &str, std::string & pattern)
{
    int M = str.length()+1, N = pattern.length()+1;
    bool dp[M][N];
    dp[0][0] = true;
    for (int i=1; i<M; i++) {
        dp[i][0] = false;
    }
    
    for (int i=1; i<N; i++) {
        if (pattern[i-1] == '*') {
            dp[0][i] = dp[0][i-2];
        } else {
            dp[0][i] = false;
        }
    }
    
    for (int i=1; i<M; i++) {
        for (int j=1; j<N; j++) {
            if (pattern[j-1] == '*') {
                // 0 ocurrance
                dp[i][j] = dp[i][j-2];
                if (!dp[i][j]) {
                    // 1 occurance
                    if (str[i-1] == pattern[j-2] || pattern[j-2] == '.') {
                        dp[i][j] = dp[i-1][j];
                    }
                }
            } else if (pattern[j-1] == '.' || str[i-1] == pattern[j-1]) {
                dp[i][j] = dp[i-1][j-1];
            } else {
                dp[i][j] = false;
            }
        }
    }
    
    return dp[M-1][N-1];
}

int zeroOneKnapsack(vector<int> & val, vector<int> & weight, int total_weight)
{
    int M = val.size()+1, N = total_weight+1;
    int dp[M][N];
    memset(dp, 0, sizeof(int)*M*N);
    for (int i=1; i<M; i++) {
        for (int j=1; j<N; j++) {
            int remaing_weight = total_weight - weight[i-1];
            if (remaing_weight >= 0) {
                // The former is to pick it, the latter is not to pick.
                dp[i][j] = max(dp[i-1][remaing_weight]+val[i-1], dp[i-1][j]);
            } else {
                dp[i][j] = dp[i-1][j];
            }
        }
    }
    
    return dp[M-1][N-1];
}

bool isAddToSum(const vector<int> &val, int sum)
{
    int M = val.size()+1, N = sum+1;
    bool dp[M][N];
    dp[0][0] = true;
    for (int i=1; i<M; i++) {
        for (int j=1; j<N; j++) {
            if (val[i-1] <= sum) {
                dp[i][j] = dp[i-1][j] || dp[i-1][sum-val[i-1]];
            } else {
                dp[i][j] = dp[i-1][j];
            }
            
        }
    }
    
    return dp[M-1][N-1];
}

int minMatriceMultiplication(vector<pair<int, int>> &matrice)
{
    int M = matrice.size();
    int dp[M][M];
    memset(dp, 0, sizeof(int)*M*M);
    for (int i=1; i<M; i++) {
        for (int j=0; j<M-i; j++) {
            // Can further simplify the following into one branch
            if (i == 1) {
                dp[j][j+i] = matrice[j].first*matrice[j].second*matrice[j+1].second;
            } else {
                int min = INT_MAX;
                for (int k=1; k<i; k++) {
                    int cur = dp[j][j+k] + dp[j+k+1][j+i] + matrice[j].first*matrice[j+k].second*matrice[j+i].second;
                    if (cur < min) {
                        min = cur;
                    }
                }
                
                dp[j][j+i] = min;
            }

        }
    }
    
    return dp[0][M-1];
}

int minEditDistance(const string& str1, const string& str2)
{
    auto M = str1.length()+1, N = str2.length()+1;
    int dp[M][N];
    memset(dp, 0, sizeof(int)*M*N);
    for (int i=1; i<N; i++) {
        dp[0][i] = i;
    }
    
    for (int i=1; i<M; i++) {
        dp[i][0] = i;
    }
    
    for (int i=1; i<M; i++) {
        for (int j=1; j<N; j++) {
            if (str1[i-1] == str2[j-1]) {
                dp[i][j] = dp[i-1][j-1];
            } else {
                dp[i][j] = min(dp[i-1][j-1], min(dp[i-1][j], dp[i][j-1]))+1;
            }
        }
    }
    
    return dp[M-1][N-1];
}

string longestPalindromeSubseq(const string& str)
{
    auto M = str.length();
    int dp[M][M];
    memset(dp, 0, sizeof(int)*M*M);
    for (int i=0; i<M; i++) {
        for (int j=0; j<M-i; j++) {
            if (i == 0) {
                dp[j][j+i] = 1;
            } else {
                if (str[j+i] == str[j]) {
                    if (i >= 2) {
                        dp[j][j+i] = 2+dp[j+1][j+i-1];
                    } else {
                        dp[j][j+i] = 2;
                    }
                } else {
                    dp[j][j+i] = max(dp[j][j+i-1], dp[j+1][j+i]);
                }
            }
        }
    }
    
    // Now get the sub seq by tracking back the matrix
    int i=0, j=M-1;
    string s;
    while (i<=j) {
        if (dp[i][j] == dp[i][j-1]) {
            j--;
        } else if (dp[i][j] == dp[i+1][j]) {
            i++;
        } else {
            s += str[i];
            i++;
            j--;
        }
    }
    
    // FIXME There is an bug is computing the offset here.
    bool offset = 1;
    if (i==j) {
        s += str[i];
        offset = 2;
    }
    
    for (int i=s.length()-offset; i>=0; i--) {
        s += s[i];
    }
    
    return s;
}

string longestPalindromeSubstr(const string& str)
{
    auto M = str.length();
    bool dp[M][M];
    memset(dp, false, sizeof(bool)*M*M);
    int max = 1;
    int start = 0;
    for (int i=0; i<M; i++) {
        for (int j=0; j<M-i; j++) {
            if (i == 0) {
                dp[j][j+i] = true;
            } else {
                if (str[j+i] == str[j] && (i==1 || dp[j+1][j+i-1])) {
                    dp[j][j+i] = true;
                }
            }
            
            if (dp[j][j+i]) {
                if (i+1>max) {
                    max = i+1;
                    start = j;
                }
            }
        }
    }
    
    return str.substr(start, max);
}

// Using memoization here
int numTreesRecur(int n, int dp[]) {
    if (n==0 || n==1)
        dp[n] = 1;
    if (dp[n] == 0) {
        int sum=0;
        for (int i=0; i<n; i++) {
            int left = numTreesRecur(i, dp);
            int right = numTreesRecur(n-1-i, dp);
            sum += left*right;
        }
        dp[n] = sum;
    }
    return dp[n];
}

int numTrees(int n) {
    int dp[n+1];
    memset(dp, 0, sizeof(int)*(n+1));
    return numTreesRecur(n, dp);
}

string wordBreak(string s, set<string> &dict) {
    auto M=s.size();
    int dp[M][M];
    memset(dp, -1, sizeof(int)*M*M);
    for (int step=0; step<M; step++) {
        for (int i=0; i<M-step; i++) {
            int j = i+step;
            if (dict.count(s.substr(i, j+1-i))) {
                dp[i][j] = i;
            } else {
                for (int k = i; k < j; k++) {
                    if (dp[i][k] != -1 && dp[k+1][j] != -1) {
                        dp[i][j] = k+1;
                        break;
                    }
                }
            }
        }
    }
    
    string res;
    int i=0, j=M-1;
    if (dp[i][j] == -1) {
        return {};
    }
    
    while (i<j) {
        int k = dp[i][j];
        if (i == k) {
            // Match entire string
            res += s.substr(i,j+1-i);
            break;
        }
        // Split match
        res += s.substr(i, k-i)+" ";
        i = k;
    }
    
    return res;
}

/*
 f(i,j) = max(v(i) + min(f(i+2, j), f(i+1, j-1),
 v(j) + min(f(i, j-2), f(i+1,j-1)))
 f(i,j) = v[i] if i == j
 f(i,j) = max(v(i), v(j)) if i == j-1
 */
int coinplay(vector<int> & coins) {
    auto M = coins.size();
    int dp[M][M];
    for (int step=0; step<M; step++) {
        for (int i=0; i<M-step; i++) {
            int j = i+step;
            if (step == 0) {
                dp[i][j] = coins[i];
            } else if (step == 1) {
                dp[i][j] = max(coins[i], coins[j]);
            } else {
                int pick_left = coins[i] + min(dp[i+2][j], dp[i+1][j-1]);
                int pick_right = coins[j] + min(dp[i][j-2], dp[i+1][j-1]);
                dp[i][j] = max(pick_left, pick_right);
            }
        }
    }
    
    return dp[0][M-1];
}

// Maximum size sub square matrix
/*
 1 0 1 1
 1 1 1 1
 1 1 1 0
 1 1 1 0 */
int maxSubmatrix(vector<vector<int>> &matrix)
{
    // Generate auxilary matrix
    // Q(i,j) = M(i,j) when i=0 || j = 0
    // Q(i,j) = 0 when any M(i,j) = 0
    // Q(i,j) = min(Q(i-1,j-1), Q(i-1, j), Q(i,j-1))+1 when M(i,j) = 1
    int M = matrix.size();
    int Q[M][M];
    for (int i=0; i<M; i++) {
        Q[i][0] = matrix[i][0];
        Q[0][i] = matrix[0][i];
    }
    
    for (int i=1; i<M; i++) {
        for (int j=1; j<M; j++) {
            if (matrix[i][j] == 0) {
                Q[i][j] = 0;
            } else {
                Q[i][j] = min(Q[i-1][j-1], min(Q[i-1][j], Q[i][j-1])) + 1;
            }
        }
    }
    
    int res = INT_MIN;
    for (int i=0; i<M; i++) {
        for (int j=0; j<M; j++) {
            if (Q[i][j] > res) {
                res = Q[i][j];
            }
        }
    }
    
    return res;
}

void dp_tests() {
    vector<int> dem = {1,2,3};
    cout << "min_change =" << coinchange2(4, dem) << endl;
    cout << "coin change tot count = " << coinchangecount(46, dem) << endl;
    vector<int> seq = {-7,1,0,2,0,3,0,4,5};
    cout << "lis = " << find_lis(seq) << endl;
    vector<vector<int>> matrix = {{1,1,1,1},{1,1,1,1},{1,1,1,1}};
    int num_of_paths = numberOfPaths(matrix);
    cout << "number of paths:" << num_of_paths << endl;
    cout << "Maxium Product Cut (15) = " << maxProductFromCutPieces(15) << endl;
    string str1 = "abfhjujk", str2 = "afukjk";
    cout << "Longest common sequence: " << longestCommonSeq(str1, str2) << endl;
    str1 = "abcd";
    str2 = "d*";
    cout << "Regex match: abcd d* = " << regexMatch(str1, str2) << endl;
    vector<int> val = {22, 20, 15, 30, 24, 54, 21, 32, 18, 25};
    vector<int> weight = {4, 2, 3, 5, 5, 6, 9, 7, 8, 10};
    cout << "Knapsack01 = " << zeroOneKnapsack(val, weight, 30) << endl;
    vector<pair<int, int>> matrice = {{2,3}, {3,6}, {6,4}, {4,5}};
    cout << "Min chain multiplication num = " << minMatriceMultiplication(matrice) << endl;
    str1="abcd", str2="bcda";
    cout << "min edit distance =" << minEditDistance(str1, str2) << endl;
    str1 = "abcbcaba";
    cout << "Longest palindrome substr = " << longestPalindromeSubstr(str1) << endl;
    cout << "Longest palindrome subsequence = " << longestPalindromeSubseq(str1) << endl;
    vector<vector<int>> b = {{1,2,1,5}, {0,3,1,1}, {1,2,1,3}};
    int dp[3][4];
    memset(dp, 0, sizeof(int)*12);
    cout << "Matrix(M,N) max sum =" << find_max_path_top_down(b, dp, 2, 3) << endl;
    set<string> myset = {"I", "like", "play", "had", "to"};
    cout << "Test word break =" << wordBreak("Ihadliketoplay", myset) << endl;
    dem = {8,15,3,7};
    cout << "Coins play maximum is " << coinplay(dem) << endl;
}
