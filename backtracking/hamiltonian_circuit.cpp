// hamiltonian circuit problem(해밀턴 회로 문제, 백트래킹)
#include <iostream>
#include <vector>

using namespace std;

bool promising(int i, int n, vector<vector<int>>& W, vector<int>& vindex) {
    int j;
    bool flag;
    if (i == n - 1 && !W[vindex[n - 1]][vindex[0]]) flag = false;
    else if (i > 0 && !W[vindex[i - 1]][vindex[i]]) flag = false;
    else {
        flag = true;
        j = 1;
        while (j < i && flag) {
            if (vindex[i] == vindex[j]) flag = false;
            j++;
        }
    }
    return flag;
}

void hamiltonian(int i, int n, vector<vector<int>>& W, vector<int>& vindex) { // 해밀턴 회로로 가능한 경우를 모두 출력하는 함수.
    int j;
    if (promising(i, n, W, vindex)) {
        if (i == n - 1) {
            for (int k = 0; k < n; k++) {
                cout << vindex[k] << " ";
            }
            cout << vindex[0] << " ";
            cout << "\n";
        } else {
            for (j = 2; j <= n; j++) {
                vindex[i + 1] = j;
                hamiltonian(i + 1, n, W, vindex);
            }
        }
    }
}
int main() {
    int n;
    cout << "정점의 수를 입력해 주세요" << "\n";
    cin >> n;
    vector<int> vindex(n, 1); // vindex 내의 i번째 index는, i번째 정점의 방문 순서를 나타낸다. 1로 초기화함으로써 시작 정점은 v1이 된다. 
    vector<vector<int>> W(n + 1, vector<int>(n + 1, 0)); // 그래프는 인접 행렬 형태로 표현됨. 
    cout << "그래프를 인접 행렬로 표현한 결과를 입력해 주세요" << "\n";
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> W[i][j];
        }
    }
    hamiltonian(0, n, W, vindex);
    return 0;
}