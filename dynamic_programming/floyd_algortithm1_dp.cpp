// floyd 알고리즘- 특정 정점에서 나머지 모든 정점으로의 최단 경로를 찾는 문제. - dp로 구현. 
// 여기서는 최소 비용만을 출력하도록 구현.
#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>

using namespace std;

void floyd(int n, vector<vector<unsigned int>>& W, vector<vector<unsigned int>>& D) {
    copy(W.begin(), W.end(), D.begin()); // W를 D로 복사.
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++ ) {
            for (int j = 1; j <= n; j++) {
                D[i][j] = min(D[i][j], D[i][k] + D[k][j]); // vi에서 vj로 직접 가는 경우와, vk를 경유해 가는 경우 중 더 작은 것 선택.
            }
        }
    }
}

int main() {
    int n;
    cout << "그래프의 정점 개수를 입력해 주세요" << "\n";
    cin >> n;
    vector<vector<unsigned int>> W(n + 1, vector<unsigned int>(n + 1, numeric_limits<int>::max()));
    vector<vector<unsigned int>> D(n + 1, vector<unsigned int>(n + 1, 0));
    cout << "이제 W를 입력해 주세요. 가는 경로가 없을 경우, -1을 입력해 주세요. " << "\n";
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            int weight;
            cin >> weight;
            if(weight == -1) {
                continue;
            } else {
                W[i][j] = weight;
            }

        }
    }
    floyd(n, W, D);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (D[i][j] == numeric_limits<int>::max()) {
                cout << 0 << " ";
            } else {
                cout << D[i][j] << " ";
            }
        }
        cout << "\n";
    }
    return 0;
}