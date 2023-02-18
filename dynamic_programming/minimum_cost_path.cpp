// 최소 비용 경로(minimum cost path) 알고리즘 - dp
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int solution(vector<vector<int>> m) {
    int rows = (int)m.size();
    int cols = (int)m[0].size();

    vector<vector<int>> dp(rows, vector<int>(cols, 0));

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if(i == 0 && j == 0) dp[i][j] = m[i][j];
            else if(x == 0) dp[i][j] = dp[i - 1][j] + m[i][j];
            else if(y == 0) dp[i][j] = dp[i][j - 1] + m[i][j];
            else dp[i][j] = min(dp[i - 1][j], dp[i][j - 1]) + m[i][j];
        }
    }
    return dp[rows - 1][cols - 1];
}