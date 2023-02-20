// binomial efficient (이항 계수) - dp로 구현
// 표현하고자 하는 범위에 따라서 int 가 아닌, 다른 자료형도 가능.
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int binomial_efficient(int n, int k, vector<vector<int>>& B) {
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= min(i, k); j++) {
            if (j == 0 || j == i) B[i][j] = 1;
            else B[i][j] = B[i - 1][j - 1] + B[i - 1][j];
        }
    }
    return B[n][k];
}
int main() {
    int n, k;
    cout << "구하고자 하는 이항계수의 n, k값을 입력해 주세요" << "\n";
    cin >> n >> k;
    vector<vector<int>> B(n + 1, vector<int>(k + 1, 0));
    cout << binomial_efficient(n, k, B);
}