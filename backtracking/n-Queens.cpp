// n-Queens 문제 (백트래킹) 
#include <iostream>
#include <cstdlib>
#include <vector>

using namespace std;

bool promising(int i, vector<int>& col) { // promising 한지 체크하는 함수. 
    int k = 1;
    bool flag = true;
    while (k < i && flag) { // 현재 row 보다 작은 row들을 탐색한다. 그리고 flag가 false가 되면 반복문을 탈출한다. 
        if (col[i] == col[k] || abs(col[i] - col[k]) == i - k) {
            flag = false;
        }
        k++;
    }
    return flag;
}

void queens (int i, int n, vector<int>& col) { // 가능한 n-Queens 문제의 해답을 모두 출력하는 함수.
    if (promising(i, col)) {
        if (i == n) { // leaf node 도달.
            for (int k = 1; k <= n; k++) {
                cout << k << " " << col[k] << "\n"; // 퀸을 배치할 열, 그리고 해당 열에서의 퀸의 위치를 출력한다. 
            }
            cout << "\n";
        } else {
            for (int j = 1; j <= n; j++) {
                col[i + 1] = j;
                queens(i + 1, n, col);
            }
        }
    }
}

int main() {
    int n; // 체스판의 크기 n
    cin >> n;
    vector<int> col(n + 1, 0);
    queens(0, n, col);
    return 0;
}