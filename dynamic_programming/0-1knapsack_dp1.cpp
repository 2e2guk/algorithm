// 0-1 배낭 문제, dp로 해결 - recursive. time complexity O(2 ^ n)
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int knapsack_0_1(int n, int W, vector<int>& w, vector<int>& p) { // 총 물건의 개수 n, 가방의 초대 무게 W, 물건들의 무게를 저장할 w, 물건들의 가치를 저장할 p
    if (n == 0 || W == 0) { // 기저 조건
        return 0;
    }
    if (w[n - 1] > W){ // 상태 전환 순환식 정의 
        return knapsack_0_1(n - 1, W, w, p);
    } else {
        return max(knapsack_0_1(n - 1, W, w, p), p[n - 1] + knapsack_0_1(n - 1, W - w[n - 1], w, p));
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
    cout << "이제 각 item들을 번호 순대로 (item 무게, item 가치) 순으로 입력해 주세요" << "\n";
    for (int i = 0; i < n; i++) {
        cin >> w[i] >> p[i];
    }
    cout << knapsack_0_1(n, W, w, p);
}