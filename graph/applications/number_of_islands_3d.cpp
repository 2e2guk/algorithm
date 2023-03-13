// 섬의 개수, 3차원으로 그래프가 주어지는 경우. 
#include <iostream>
#include <vector>
#include <stack>
#include <set>

using namespace std;

class NumIslands {
public:
    int count(vector<vector<vector<int>>>& grid) {
        int rows = grid.size();
        if (rows == 0) return 0;
        int cols = grid[0].size();
        if (cols == 0) return 0;
        int heights = grid[0][0].size();
        if (heights == 0) return 0;

        this->grid = grid;
        this->rows = rows;
        this->cols = cols;
        this->heights = heights;

        int numIslands = 0;

        for (int z = 0; z < heights; z++) {
            for (int y = 0; y < rows; y++) {
                for (int x = 0; x < cols; x++) {
                    if (this->grid[z][y][x] == 1) {
                        numIslands++;
                        this->dfs(z, y, x);
                    }
                }
            }
        }

        return numIslands;
    }

private:
    vector<vector<vector<int>>> grid;
    int rows, cols, heights;

    bool isValid(int z, int y, int x) {
        return z >= 0 && y >= 0 && x >= 0 && z < this->heights && y < this->rows && x < this->cols && this->grid[z][y][x] == 1;
    }

    void dfs(int z, int y, int x) {
        stack<vector<int>> s;
        set<vector<int>> seen;

        s.push({z, y, x});
        seen.insert({z, y, x});

        while (!s.empty()) {
            vector<int> cur = s.top();
            s.pop();

            int cur_z = cur[0], cur_y = cur[1], cur_x = cur[2];
            this->grid[cur_z][cur_y][cur_x] = 0;
            
            // 그래프를 탐색하는 방향이 6방향으로 늘어났다. 
            vector<vector<int>> next_pos = {{cur_z - 1, cur_y, cur_x}, {cur_z, cur_y - 1, cur_x}, {cur_z, cur_y, cur_x - 1},
                                            {cur_z, cur_y, cur_x + 1}, {cur_z, cur_y + 1, cur_x}, {cur_z + 1, cur_y, cur_x}};
            for (vector<int> pos : next_pos) {
                int next_z = pos[0], next_y = pos[1], next_x = pos[2];
                if (isValid(next_z, next_y, next_x) && seen.count({next_z, next_y, next_x}) == 0) {
                    s.push({next_z, next_y, next_x});
                    seen.insert({next_z, next_y, next_x});
                }
            }
        }
    }
};

int main() {
    int row, col, height;
    cout << "(row X col X height) 형태의 인접 행렬에서, row, col, height 값을 입력해 주세요!" << "\n";
    cin >> row >> col >> height;
    cout << "이제, 인접 행렬을 입력해 주세요!" << "\n";
    vector<vector<vector<char>>> matrix(height, vector<char>(row, vector<char>(col, '0')));
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < row; j++) {
            for (int k = 0; k < col; k++) {
                cin >> matrix[i][j][k];
            }
        }
    }
    NumIslands numIslands;
    cout << "섬의 개수는 다음과 같습니다: " << numIslands.count(matrix) << "\n";
    return 0;
}