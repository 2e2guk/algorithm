// 0-1 배낭 문제 - 백트래킹으로 해결.
#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>

using namespace std;

bool promising(int i, int n, int W, int weight, int profit, vector<int>& w, vector<int>& p, int maxprofit) {
    int j, k, totweight;
    double bound;

    if (weight >= W) {
        return false;
    } else {
        j = i + 1;
        bound = profit;
        totweight = weight;
        while (j <= n && totweight + w[j - 1] <= W) {
            totweight = totweight + w[j - 1];
            bound = bound + p[j - 1];
            j++;
        }
        k = j;
        if (k <= n) {
            bound += (W - totweight) * (double)p[k - 1] / w[k - 1];
        }
        return bound > maxprofit;
    }
}

vector<int> knapsack_0_1_backtracking(int i, int n, int W, int weight, int profit, vector<int>& w, vector<int>& p, vector<bool>& is_included, int maxprofit) {
    vector<int> bestset(n, 0);
    if (weight <= W && profit > maxprofit) {
        maxprofit = profit;
        copy(is_included.begin(), is_included.end(), bestset.begin());
    }
    if (promising(i, n, W, weight, profit, w, p, maxprofit)) {
        is_included[i + 1] = true;
        knapsack_0_1_backtracking(i + 1, n, W, weight + w[i + 1], profit + p[i + 1], w, p, is_included, maxprofit);
        is_included[i + 1] = false;
        knapsack_0_1_backtracking(i + 1, n, W, weight, profit, w, p, is_included, maxprofit);
    }
    return bestset;
}
int main() {
    int n, W;
    int weight, profit, maxprofit = 0;
    cout << "item의 개수를 입력해 주세요: " << "\n";
    cin >> n;
    cout << "가방이 버틸 수 있는 최대의 무게를 입력해 주세요: " << "\n";
    cin >> W;
    vector<int> w(n, 0);
    vector<int> p(n, 0);
    cout << "item의 무게와 가치를, 순서대로 입력해 주세요!" << "\n";
    for (int i = 0; i < n; i++) {
        cin >> w[i] >> p[i];
    }
    vector<bool> is_included(n, false);
    for(auto ele : knapsack_0_1_backtracking(0, n, W, weight, profit, w, p, is_included, maxprofit)) {
        cout << ele << " ";
    }
    return 0;
}