// 최소 갯수 동전 바꾸기. - dp로 해결.
// 주어진 동전 coins로 금액의 합 amount 를 만들기 위한 최소한의 동전의 갯수를 구한다. - 각 동전들은 무제한으로 사용 가능하다. 
#include <vector>
#include <algorithm>
#include <iostream>
#include <limits>

using namespace std;

int coinChange(vector<int>& coins, int amount) {
    const int MAX_COST = numeric_limits<int>::max();
    vector<int> dp_array(amount + 1, -1);

    // 0이라는 값을 만들기 위해서 필요한 동전의 개수는 0개이다. 
    dp_array[0] = 0;

    // dp_array[n] 에는, n이라는 값을 만들기 위해서 필요한 최소한의 동전 개수가 들어간다. 
    for (int idx = 0; idx <= amount; idx++) {
        // dp_array[idx]가 -1인 경우는, 아직 해당 값을 구하지 못한 경우이다.(초기화되어 있는 상태.)
        if (dp_array[idx] != -1) {
            continue;
        }

        int crnt_min = MAX_COST;
        // coins에 1, 2, 3이 있는 경우를 생각해 보자. 이때 dp_array[n] = min(dp_array[n - 1], dp_array[n - 2], dp_array[n - 3]) + 1이다.
        // 각각의 동전을 포함시키지 않는 경우를 생각하고, 해당 경우의 최솟값을 선택하고, bottom-up 방식으로 해결할 때, 제외시킨 동전을 포함하므로, 1을 더해 준다.  
        for (int coin : coins) {
            int last_idx = idx - coin;

            // iast_idx < 0 인 경우는, 당연히 불가능한 경우이다. 동전의 가치를 합해서 음수가 나오는 경우는 존재하지 않는다. 
            if (last_idx < 0) {
                continue;

            }

            // last_cost 는 현재 index의 dp_array값이다. 현재 index의 가치를 만들기 위해서 필요한 최소한의 동전 개수가 저장되어 있다. 
            int last_cost = dp_array[last_idx];

            // 만약 last_cost 값이 -1인 경우는, 해당 가치를 만들 수 있는 동전이 존재하지 않는 경우이므로, invalid한 경우이다. 
            if (last_cost == -1) {
                continue;
            }

            // 동전들의 리스트 coins에서 임의의 동전을 제외시키고 구한, 최소 동전 개수에, 현재 동전을 포함시킨다. (+1)
            int cost = last_cost + 1;

            // crnt_min은 현재 index의 가치를 만드는 데 필요한 최소한의 동전 개수이다. 초기값의 경우, crnt_min값이 INT_MAX값으로 설정되어 있기 때문에 무조건 cost를 선택하지만, 
            // 그 이후에는, 이전에 구한 crnt_min값과, 현재 cost값을 이용해서, crnt_min값을 갱신시킨다. +1을 하지 않는 이유는, 처음엔 무조건 cost = last_cost + 1값이 선택되었고,
            // 그 이후엔 새로 구한 cost 값과의 비교를 실시하므로, 위의 예시에서 dp_array[n] = min(dp_array[n - 1] + 1, dp_array[n - 2] + 1, dp_array[n - 3] + 1) 을 한 것과 동일하다. 
            crnt_min = min(cost, crnt_min);
        }
        
        // dp_array[idx] 값은 만약 crnt_min값이 초깃값  MAX_COST값에서 갱신되지 않았다면 invalid한 경우이므로 -1을 저장, 그렇지 않다면, 구한 crnt_min값을 이용한다. 
        dp_array[idx] = (crnt_min == MAX_COST) ? -1 : crnt_min;
    }

    return dp_array[amount];
}

int main() {
    int coin_num;
    cout << "동전의 종류의 수를 입력해 주세요!" << "\n";
    cin >> coin_num;
    vector<int> coins(coin_num, 0);
    for (int i = 0; i < coin_num; i++) {
        cin >> coins[i];
    }
    int amount;
    cout << "동전으로 만들고자 하는 가치를 입력해 주세요!" << "\n";
    cin >> amount;
    cout << coinChange(coins, amount) << "\n";
    return 0;
}