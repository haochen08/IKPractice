//
//  dp.cpp
//  Lesson-1
//
//  Created by Hao Chen on 16/10/8.
//  Copyright © 2016年 HaoChen. All rights reserved.
//

#include <iostream>
#include <vector>
#include "dp.hpp"

using namespace std;

template<class T>
void init_dp(vector<vector<T>> &dp, int M, int N)
{
    dp.resize(M);
    for (auto &i : dp) {
        i.resize(N);
    }
}

int coinchange(int amount, std::vector<int> &denom)
{
    vector<int> cache;
    cache.resize(amount+1);
    
    for (int a=0; a<=amount; a++) {
        if (a == 0) {
            cache[a] = 0;
        } else {
            int min = INT_MAX;
            int ans;
            for (int d:denom) {
                if (a >= d) {
                    ans = cache[a-d];
                    if (ans != INT_MAX) {
                        min = std::min(ans+1, min);
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

int longestCommonSeq(std::string & str1, std::string & str2)
{
    vector<vector<int>> dp;
    int M = str1.length()+1, N = str2.length()+1;
    init_dp(dp, M, N);
    
    int res = INT_MIN;
    for (int i=1; i<M; i++) {
        for (int j=1; j<N; j++) {
            if (str1[i-1] == str2[j-1]) {
                dp[i][j] = dp[i-1][j-1]+1;
            } else {
                dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
            }
            
            if (dp[i][j] > res) {
                res = dp[i][j];
            }
        }
    }
    
    return res;
}

// Pattern can have '.' '*'
bool regexMatch(std::string &str, std::string & pattern)
{
    vector<vector<bool>> dp;
    int M = str.length()+1, N = pattern.length()+1;
    init_dp(dp, M, N);
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
    vector<vector<int>> dp;
    int M = val.size()+1, N = total_weight+1;
    init_dp(dp, M, N);
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
    vector<vector<bool>> dp;
    int M = val.size()+1, N = sum+1;
    init_dp(dp, M, N);
    dp[0][0] = true;
    for (int i=1; i<M; i++) {
        for (int j=1; j<N; j++) {
            if (val[i-1] >= sum) {
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
    vector<vector<int>> dp;
    int M = matrice.size();
    init_dp(dp, M, M);
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

void dp_tests() {
    vector<int> dem = {1,11,13};
    int min_change = coinchange(46, dem);
    vector<int> seq = {-7,1,0,2,0,3,0,4,5};
    cout << min_change << endl;
    cout << "lis = " << find_lis(seq) << endl;
    vector<vector<int>> matrix = {{1,1,1,1},{1,1,1,1},{1,1,1,1}};
    int num_of_paths = numberOfPaths(matrix);
    cout << "number of paths:" << num_of_paths << endl;
    cout << "Maxium Product Cut (15) = " << maxProductFromCutPieces(15) << endl;
    string str1 = "abfhjujk", str2 = "afukjk";
    cout << "Longest common sequence " << longestCommonSeq(str1, str2) << endl;
    str1 = "abcd";
    str2 = "d*";
    cout << "Regex match: abcd d* = " << regexMatch(str1, str2) << endl;
    vector<int> val = {22, 20, 15, 30, 24, 54, 21, 32, 18, 25};
    vector<int> weight = {4, 2, 3, 5, 5, 6, 9, 7, 8, 10};
    cout << "Knapsack01 = " << zeroOneKnapsack(val, weight, 30) << endl;
    vector<pair<int, int>> matrice = {{2,3}, {3,6}, {6,4}, {4,5}};
    cout << "Min chain multiplication num = " << minMatriceMultiplication(matrice) << endl;
    
}
