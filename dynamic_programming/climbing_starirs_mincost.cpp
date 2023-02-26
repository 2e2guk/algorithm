// 최소 비용 계단 오르기 - dp로 해결
// i번째 계단을 오르는 비용이 cost[i] 로 주어진다. 계단은 한번에 한칸 혹은 두칸만 오를 수 있다. 이때, 전체 계단을 오르는데 필요한 최소 비용을 구하라. 
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// 계단을 오르는 최소 비용을 반환하는 함수. 
int minCostStairs(vector<int>& cost) {
    int total_count = cost.size();
    vector<int> min_cost(total_count + 1, 0);
    // n번째 계단에 올라오는 방법은 n-1번쨰 계단에서 올라오거나, n-2번째 계단에서 올라오는 방법이 있다. 
    for (int i = 2; i <= total_count; i++) {
        // n-1번째 계단까지의 최소 비용 + n-1번째 계단을 밟는데 필요한 비용
        int one_step = min_cost[i - 1] + cost[i - 1];

        // n-2번째 계단까지의 최소 비용 + n-2번째 계단을 밟는데 필요한 비용
        int two_step = min_cost[i - 2] + cost[i - 2];
        min_cost[i] = min(one_step, two_step);
    }

    return min_cost[total_count];
}

int main() {
    int stairnum;
    vector<int> cost;
    cout << "계단의 개수를 입력해 주세요: " << "\n";
    cin >> stairnum;
    cout << "첫 번째 계단부터 n번쨰 계단까지 계단을 밟는데 필요한 비용을 입력해 주세요:" <<"\n";
    for (int i = 0; i < stairnum; i++) {
        int input;
        cin >> input;
        cost.push_back(input);
    }
    cout << "Minimum cost: " << minCostStairs(cost) << endl;
    return 0;
}
