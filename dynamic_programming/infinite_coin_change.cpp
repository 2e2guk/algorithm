// 무제한 동전바꾸기. - 이것도 0-1 knapsack 문제의 변형이다. "동전이 포함되는지/포함되지 않는지" 가 중요하지만, 
// 차이점이 있다면 이 경우, 특정 동전이 포함되는 경우에, 해당 동전이 몇 개 포함되는지까지 고려해야 한다. 
// 동전의 종류 리스트가 주어진다. 이때, 각 종류의 동전은 무한히 사용할 수 있다. 이 경우, 주어진 동전들로, amount 값을 만들 수 있는 경우는 몇 가지인가?
#include <iostream>
#include <vector>

using namespace std;

// 주어진 동전 리스트로 amount 값을 만들 수 있는 경우가 몇 가지인지 반환하는 함수. 
int coinChange(int amount, vector<int>& coins) {
    
    // dp_table[i][j] = i번째 index까지의 원소들로, j를 만들 수 있는 경우의 수.
    // dp(n, s) = dp(n - 1, s) + dp(n, s - nth coin)
    // 공집합, amount가 0인 경우를 고려해야 하므로  +1을 해 준다. 
    vector<vector<int>> dp_table(coins.size() + 1, vector<int>(amount + 1, 0));
    
    // 초기화. dp_table[i][0] = 1이다. 어떤 집합이 주어지던, 동전을 전부 선택하지 않는 경우, 그 값은 0이기 때문에, 1가지 경우가 있다. 
    for (int rowIdx = 0; rowIdx < dp_table.size(); rowIdx++) {
        dp_table[rowIdx][0] = 1;
    }
    
    // rowidx가 1부터 시작하므로, 첫 번째 원소를 참조하려면 rowidx - 1을 해 줘야 한다. 
    for (int rowIdx = 1; rowIdx < dp_table.size(); rowIdx++) {
        int coin = coins[rowIdx - 1];
        int prev_row = rowIdx - 1;
        for (int colIdx = 1; colIdx < dp_table[rowIdx].size(); colIdx++) {
            // dp0은, 특정 동전을 1개만 포함한 경우에 해당한다. dp(n, s - nth coin).
            int dp0 = 0;
            int prev_col = colIdx - coin;
            if (0 <= prev_col) {
                dp0 = dp_table[rowIdx][prev_col];
            }
            // dp1은, 특정 동전을 포함시키지 않는 경우에 해당한다. dp(n - 1, s).
            int dp1 = dp_table[prev_row][colIdx];

            // dp(n, s) = dp(n - 1, s) + dp(n, s - nth coin)
            int dp = dp0 + dp1;
            dp_table[rowIdx][colIdx] = dp;
        }
    }
  
    return dp_table[coins.size()][amount];
}

int main() {
    int coin_nums, amount;
    cout << "동전의 종류릐 수와, 만들고자 하는 값을 입력해 주세요!" << "\n";
    cin >> coin_nums >> amount;
    vector<int> coins(coin_nums, 0);
    cout << "이제 동전의 종류를 입력해 주세요!" < "\n";
    for (int i = 0; i < coin_nums; i++) {
        cin >> coins[i];
    }
    cout << coinChange(amount, coins) << endl;
    return 0;
}
