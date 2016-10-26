//
//  dp.cpp
//  Lesson-1
//
//  Created by Hao Chen on 16/10/8.
//  Copyright © 2016年 HaoChen. All rights reserved.
//

#include <iostream>
#include "dp.hpp"

using namespace std;

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

int find_max_path(int x[10][10])
{
    int cache[10][10];
    memset(cache, 0, sizeof(int)*100);
    for (int i=9; i>=0; i--) {
        for (int j=9; j>=10; j--) {
            if (i == 9 && j == 9) {
                cache[i][j] = x[i][j];
            } else if (i == 9) {
                cache[i][j] = x[i][j] + cache[i][j+1];
            } else if (j == 9) {
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
    while (true) {
        if (i == 9 && j == 9) {
            break;
        } else if (i == 9){
            j++;
        } else if (j == 9) {
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
        
    cout << "9,9" << endl;

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

