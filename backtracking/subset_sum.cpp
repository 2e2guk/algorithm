// subset_sum (부분집합의 합 문제) 
#include <iostream>
#include <vector>
#include <numeric> // std::accumulate 
#include <algorithm> // std::sort

using namespace std;

bool promising(int i, int weight, int total, int W, vector<int>& w) {
    return (weight + total >= W) && (weight == W || weight + w[i + 1] <= W);
}

void sum_of_subsets(int i, int weight, int total, int W, vector<bool>& is_included, vector<int>& w) {
    if (promising(i, weight, total, W, w)) {
        if (weight == W) {
            for (int j = 1; j <= i; j++) {
                if(is_included[j] == true) 
                    cout << w[j] << " ";
            }
            cout << "\n";
        } else {
            is_included[i + 1] = true;
            sum_of_subsets(i + 1, weight + w[i + 1], total - w[i + 1], W, is_included, w);
            is_included[i + 1] = false;
            sum_of_subsets(i + 1, weight, total - w[i + 1], W, is_included, w);
        }
    }
}

int main() {
    int n, total, W;
    int weight = 0;
    cin >> n >> W;
    vector<bool> is_included(n + 1, false);
    vector<int> w(n + 1, 0);
    for (int k = 1; k <= n; k++) {
        cin >> w[k];
    }
    total = accumulate(w.begin() + 1, w.end(), 0); 
    sort(w.begin(), w.end());
    sum_of_subsets(0, weight, total, W, is_included, w);
    return 0;
}
