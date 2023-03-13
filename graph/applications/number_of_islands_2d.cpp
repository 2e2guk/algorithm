// 그래프가 인접 행렬 형태로 주어질 때, 0은 물을, 1은 땅을 의미한다. 이때, matrix 내의 섬의 개수를 구하여라. 
#include <iostream>
#include <vector>
#include <set>
#include <stack>

using namespace std;

class NumIslands {
public:
    // 인접 행렬로 주어진 그래프에서, 섬의 개수를 반환하는 함수.
    int count(vector<vector<char>>& grid) {
        int rows = grid.size();
        if (rows == 0) return 0;
        int cols = grid[0].size();
        if (cols == 0) return 0;
        
        // 해당 객체의 private로 선언된 grid, rows, cols에, public에서 선언된 grid, rows, cols 값을 할당한다. 
        this->grid = grid;
        this->rows = rows;
        this->cols = cols;
        
        int numIslands = 0;
        
        for (int y = 0; y < rows; y++) {
            for (int x = 0; x < cols; x++) {
                // 인접 행렬로 주어진 그래프의 모든 정점을 순회하면서, 만약 땅을 만나게 되는 경우,
                // 섬의 개수 numIaslands를 늘려 주고, dfs를 수행한다. 
                if (this->grid[y][x] == '1') {
                    numIslands++;
                    this->dfs(y, x);
                }
            }
        }
        
        return numIslands;
    }

private:

    vector<vector<char>> grid;
    int rows, cols;
    
    // 현재 탐색중인 위치가 유효한 위치인지 알아본다 
    // y >= 0 && x >= 0 && y < this->rows && x < this->cols 탐색중인 위치는 matrix를 벗어날 수 없다. 
    // this->grid[y][x] == '1' 현재 탐색중인 위치에 땅이 있어야 한다. 
    bool isValid(int y, int x) {
        return y >= 0 && x >= 0 && y < this->rows && x < this->cols && this->grid[y][x] == '1';
    }
    
    // 현재 정점(row, col)에서, dfs를 수행하는 함수. 
    void dfs(int row, int col) {
        stack<pair<int, int>> s;
        set<pair<int, int>> seen;
        
        s.push({row, col});
        seen.insert({row, col});
        
        while (!s.empty()) {
            pair<int, int> cur = s.top();
            s.pop();
            
            int y = cur.first, x = cur.second;
            this->grid[y][x] = '0';
            
            // 현재 정점의 상하좌우를 탐색한다. 
            vector<pair<int, int>> idx_pairs = {{y - 1, x}, {y, x + 1}, {y + 1, x}, {y, x - 1}};
            for (pair<int, int> idx_pair : idx_pairs) {
                int next_y = idx_pair.first, next_x = idx_pair.second;
                // 현재 탐색 위치가 유효하고, 방문하지 않았다면, stack, seen 에 push 한다. 
                if (isValid(next_y, next_x) && seen.count({next_y, next_x}) == 0) {
                    s.push({next_y, next_x});
                    seen.insert({next_y, next_x});
                }
            }
        }
    }
};

int main() {
    int row, col;
    cout << "(n X m) 형태의 인접 행렬에서, n, m 값을 입력해 주세요!" << "\n";
    cin >> row >> col;
    cout << "이제, 인접 행렬을 입력해 주세요!" << "\n";
    vector<vector<char>> matrix(row, vector<char>(col, '0'));
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            cin >> matrix[i][j];
        }
    }
    NumIslands numIslands;
    cout << "섬의 개수는 다음과 같습니다: " << numIslands.count(matrix) << "\n";
    return 0;
}
