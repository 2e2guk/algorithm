// 최소 비용 길찾기. - dp로 해결
// 2d array로 길을 가기 위한 비용이 주어진다. 왼쪽 위에서, 오른쪽 아래로 가기 위한 최소 비용을 구하라. 
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// 최소 비용 경로를 구하는 함수. 
int minPathSum(vector<vector<int>>& grid) {
    int rows = grid.size();
    int cols = grid[0].size();

    vector<vector<int>> minCost2d(rows, vector<int>(cols, 0));

    // 2d cost를 초기화한다.(기저 조건 정의) - row값이 0인 경우는 왼쪽에서 오는 방법밖에 없으며, col값이 0인 경우는 오른쪽에서 오는 방법밖에 없다. 

    // 시작 위치의 값은 그대로 사용한다. 
    minCost2d[0][0] = grid[0][0];

    for (int colIdx = 1; colIdx < cols; colIdx++) {
        minCost2d[0][colIdx] = grid[0][colIdx] + minCost2d[0][colIdx-1];
    }
    for (int rowIdx = 1; rowIdx < rows; rowIdx++) {
        minCost2d[rowIdx][0] = grid[rowIdx][0] + minCost2d[rowIdx-1][0];
    }

    // bottom up DP
    for (int rowIdx = 1; rowIdx < rows; rowIdx++) {
        for (int colIdx = 1; colIdx < cols; colIdx++) {
            int prevCol = colIdx - 1;
            int prevRow = rowIdx - 1;

            // upcost는 바로 위에서 내려오는 경우이다. - 0인 경우는 이전 행이 존재하지 않는 경우이다. 이 경우 upcost값은 0으로 초기화한다.
            int upCost = (prevRow < 0) ? 0 : minCost2d[prevRow][colIdx];

            // leftcost는 왼쪽 대각선 위에서 내려오는 경우이다.  - 0인 경우는 이전 열이 존재하지 않는 경우이다. 이 경우 leftcot값은 0으로 초기화된다. 
            int leftCost = (prevCol < 0) ? 0 : minCost2d[rowIdx][prevCol];

            // 현재 index로 올 수 있는 두 가지 경로 중에서, 더 작은 값을 선택한다. 
            int prevCost = min(upCost, leftCost);

            // cost값은, 이전 경로 중에서 가장 작은 값과, 현재 index에서의 cost값을 더해서 구한다. 
            int cost = prevCost + grid[rowIdx][colIdx];
            minCost2d[rowIdx][colIdx] = cost;
        }
    }

    // 마지막 index에 해당하는 minCost2d값을 반환한다. 
    int minCost = minCost2d[rows - 1][cols - 1];
    return minCost;
}

int main() {
    int n;
    cout << "각 길의 비용이 들어간 nXn 이차원 벡터의 n값을 입력해 주세요. " << "\n";
    cin >> n;
    vector<vector<int>> grid(n, vector<int>(n, 0));
    cout << "각 길의 비용이 들어간 nXn 이차원 벡터의 element 들을 입력해 주세요. " << "\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> grid[i][j];
        }
    }
    cout << "minCost = " << minPathSum(grid) << endl;
    return 0;
}
