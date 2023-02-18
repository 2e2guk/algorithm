// 0-1 배낭 문제, dp로 해결 - 메모이제이션을 이용하지만, 2차원 배열을 선언하는 것이 아닌, std::map, std::pair 를 이용해 공간 복잡도 향상. 
#include <iostream>
#include <vector>
#include <map>
#include <utility> // std::pair header
#include <algorithm>

using namespace std;

int improved_spacecomplex_knapscak(int n, int W, vector<int>& w, vector<int>& p, map<pair<int, int>, int>& dp) {
    if (n == 0 || W == 0)
        return 0;
    int lvalue = (dp.find(make_pair(n - 1, W)) != dp.end()) ?  // 이미 dp[n - 1][W]값이 계산되어 있다면 그대로 리턴, 아닌 경우 재귀 호출
        dp[make_pair(n - 1, W)] : improved_spacecomplex_knapscak(n - 1, W, w, p, dp);
    int rvalue = (dp.find(make_pair(n - 1, W - w[n])) != dp.end()) ? 
        dp[make_pair(n - 1, W - w[n])] : improved_spacecomplex_knapscak(n - 1, W - w[n], w, p, dp);
    dp[make_pair(n, W)] = (w[n] > W) ? lvalue : max(lvalue, p[n] + rvalue);
    return dp[make_pair(n, W)];
}

int main () {
    int n, W;
    cout << "item  의 개수: " << "\n";
    cin >> n;
    cout << "배낭에 담을 수 있는 최대의 무게" << "\n";
    cin >> W;
    vector<int> w(n + 1, 0); // 물품들의 무게.
    vector<int> p(n + 1, 0); // 물픔들의 이익.
    map<pair<int, int>, int> dp;
    cout << "이제 각 item들을 번호 순대로 (item 무게, item 가치) 순으로 입력해 주세요" << "\n";
    for (int i = 0; i < n; i++) {
        cin >> w[i] >> p[i];
    }
    cout << improved_spacecomplex_knapscak(n - 1, W, w, p, dp); // index 가 0부터 시작하므로, n - 1로 호출해야 한다. 
    return 0;
}