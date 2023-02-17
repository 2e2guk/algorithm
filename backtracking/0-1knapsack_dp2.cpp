// 0-1 배낭 문제, dp로 해결 - memoization. time complexity O(n * W)
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int knapsack_0_1_memo(int i, int W, vector<int>& w, vector<int>& p, vector<vector<int>>& dp) { // 총 물건의 개수 n, 가방의 초대 무게 W, 물건들의 무게를 저장할 w, 물건들의 가치를 저장할 p
    if (i < 0) // 기저 조건
        return 0;
    if(dp[i][W] != -1) // memoization
        return dp[i][W];
    if (w[i] > W) { // 배낭에 item을 담을 수 없는 경우.
        dp[i][W] = knapsack_0_1_memo(i - 1, W, w, p, dp);
        return dp[i][W];
    } else { // 배낭에 item을 담을 수 있는 경우. item을 담을 순 있지만 담지 않은 경우와, 배낭에 item을 직접 담은 경우 중에서 더 큰 값을 선택한다. 
        dp[i][W] = max(knapsack_0_1_memo(i - 1, W, w, p, dp), p[i] + knapsack_0_1_memo(i - 1, W - w[i], w, p, dp));
        return dp[i][W];
    }
}

int main() {
    int n, W;
    cout << "item  의 개수: " << "\n";
    cin >> n;
    cout << "배낭에 담을 수 있는 최대의 무게" << "\n";
    cin >> W;
    vector<int> w(n + 1, 0); // 물품들의 무게.
    vector<int> p(n + 1, 0); // 물픔들의 이익.
    vector<vector<int>> dp(n, vector<int>(W + 1, -1));
    cout << "이제 각 item들을 번호 순대로 (item 무게, item 가치) 순으로 입력해 주세요" << "\n";
    for (int i = 0; i < n; i++) {
        cin >> w[i] >> p[i];
    }
    cout << knapsack_0_1_memo(n - 1, W, w, p, dp); // index 가 0부터 시작하므로, n - 1로 호출해야 한다. 
    return 0;
}
