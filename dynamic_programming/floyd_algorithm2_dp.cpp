// floyd 알고리즘- 특정 정점에서 나머지 모든 정점으로의 최단 경로를 찾는 문제. - dp로 구현. 
// 여기서는 최소 비용을 경유하는 경로를 출력하도록 구현. 
#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>

using namespace std;

void floyd(int n, vector<vector<unsigned int>>& W, vector<vector<unsigned int>>& D, vector<vector<unsigned int>>& P) { // 플로이드 알고리즘.
    copy(W.begin(), W.end(), D.begin()); // W를 D로 복사. D0(= W).
    for (int k = 1; k <= n; k++) { // D0(= W), D1, D2 , ... , Dn(= D) 로 순차적으로 update.
        for (int i = 1; i <= n; i++ ) {
            for (int j = 1; j <= n; j++) {
                if (D[i][k] + D[k][j] < D[i][j]) {
                    P[i][j] = k;
                    D[i][j] = D[i][k] + D[k][j];
                }
            }
        }
    }
}

void path(int start, int end, vector<vector<unsigned int>>& P) { // vstart, vend 로의 최소 비용 경로를 출력하는 함수. 
    if (P[start][end] != 0) {
        path(start, P[start][end], P);
        cout << P[start][end] << " ";
        path(P[start][end], end, P);
    }
}

int main() {
    int n;
    cout << "그래프의 정점 개수를 입력해 주세요" << "\n";
    cin >> n;
    vector<vector<unsigned int>> W(n + 1, vector<unsigned int>(n + 1, numeric_limits<int>::max()));
    vector<vector<unsigned int>> D(n + 1, vector<unsigned int>(n + 1, 0));
    vector<vector<unsigned int>> P(n + 1, vector<unsigned int>(n + 1, 0)); // P[i][j] = vi에서 vj까지 경유하는 정점 중 index가 최대인 것을 저장하는 배열.
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
    floyd(n, W, D, P);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cout << "now " << i << " , " << j << " = ";
            if (i == j) {
                cout << "\n";
                continue;
            }
            cout << i << " ";
            path(i, j, P);
            cout << j << " ";
            cout << "\n";
        }
    }
    return 0;
}