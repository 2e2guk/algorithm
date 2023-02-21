// m-coloring 문제(백트래킹)
// 그래프는 인접 행렬로 표현하였다. 
// vcolor에 1번~m번 색까지 입력된다. 출력이 1 2 3 2 인 경우, 1번 정점은 1번 색으로, 2번 정점은 2번 색으로, 3번 정점은 3번 색으로, 4번 정점은 2번 색으로 칠하라는 의미이다. 
#include <iostream>
#include <vector>

using namespace std;

bool promising(int i, vector<vector<int>>& W, vector<int>& vcolor) {
    int j = 1;
    bool flag = true;
    while (j < i && flag) {
        if (W[i][j] && vcolor[i] == vcolor[j]) 
            flag = false;
        j++;
    }
    return flag;
}

void m_coloring(int i, int n, int m, vector<vector<int>>& W, vector<int>& vcolor) { // i = 현재 SST에서의 level.

    int color;

    if (promising(i, W, vcolor)) {
        if (i == n) { // 마지막 level 까지 내려간 경우.
            for(int k = 1; k <= n; k++) {
                cout << vcolor[k] << " ";
            }
            cout << "\n";
        } else {
            for (color = 1; color <= m; color++) {
                vcolor[i + 1] = color;
                m_coloring(i + 1, n, m, W, vcolor);
            }
        }
    }
}

int main() {
    int n, m;
    cout << "그래프가 몇 개의 정점을 가지고 있는지 입력해 주세요" << "\n";
    cin >> n;
    cout << "그래프를 몇 가지 색깔로 칠할 것인지 입력해 주세요" << "\n";
    cin >> m;
    vector<vector<int>> W(n + 1, vector<int>(n + 1, 0)); // 그래프는 인접 행렬 형태로 주어진다. 
    vector<int> vcolor(n, 1); // 그래프의 각 정점에 무슨 색깔이 들어갈지 저장하는 vector. vcolor[1]에는 1번 정점에 무슨 색이 들어갈지가 입력된다. 

    cout << "그래프를 인접 행렬로 표현해 주세요" << "\n";
    for (int i = 1; i <= n; i++) { // 인접 행렬로 그래프를 표현해 입력해 준다.
        for (int j = 1; j <= n; j++) {
            cin >> W[i][j];
        }
    }
    cout << "result" << "\n";
    m_coloring(0, n, m, W, vcolor); // 시작 level 은 0이다. 
    return 0;
}

