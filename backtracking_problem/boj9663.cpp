// boj 9663 N-Queen
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

int queens (int i, int n, vector<int>& col, int& count) { // 가능한 n-Queens 문제의 해답을 모두 출력하는 함수.
    if (promising(i, col)) {
        if (i == n) { // leaf node 도달.
            count++;
        } else {
            for (int j = 1; j <= n; j++) {
                col[i + 1] = j;
                queens(i + 1, n, col, count);
            }
        }
    }
    return count;
}

int main() {
    int n; // 체스판의 크기 n
    int count = 0;
    cin >> n;
    vector<int> col(n + 1, 0);
    cout << queens(0, n, col, count);
    return 0;
}