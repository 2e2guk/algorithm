// 그래프가 2차원 martix 형태로 주어질 때, 최단 경로를 구하는 알고리즘 0은 길을, 1은 장애물을 의미한다. 
// 구현에 BFS를 사용하는데, BFS로 구한 경로는 최단 경로임이 보장되어 있기 때문이다. 
#include <iostream>
#include <vector>
#include <deque>
#include <set>

using namespace std;

class ShortestPath
{
public:

    // 최단 경로를 구하는 BFS
    int BFS(vector<vector<int>> grid)
    {
        int rows = grid.size();
        if (rows == 0)
            return -1;
        int cols = grid[0].size();
        if (cols == 0)
            return -1;

        // 처음부터 장애물이 있는 경우에는 시작할 수가 없다. 
        if (grid[0][0] != 0)
            return -1;

        // 해당 객체의 private에 선언된 멤버 변수에, public에 선언된 멤버 변수들을 할당. 
        this->_rows = rows;
        this->_cols = cols;
        this->_grid = grid;

        deque<pair<int, int>> queue;
        
        // 현재까지의 최단 경로의 거리를 저장하는 deque.
        deque<int> countQ;
        set<pair<int, int>> seen;
        queue.push_back({0, 0});
        countQ.push_back(1);
        seen.insert({0, 0});
        while (!queue.empty())
        {
            pair<int, int> cur = queue.front();
            queue.pop_front();
            int count = countQ.front();
            countQ.pop_front();
            int y = cur.first, x = cur.second;
            this->_grid[y][x] = count;

            // 탈출 조건. 현재 마지막에 도달한 경우. 
            if (y == this->_rows - 1 && x == this->_cols - 1)
                return count;
            vector<pair<int, int>> idx_pairs = {{y - 1, x - 1}, {y - 1, x}, {y - 1, x + 1}, {y, x + 1}, {y + 1, x + 1}, {y + 1, x}, {y + 1, x - 1}, {y, x - 1}};
            idx_pairs = this->filter(idx_pairs);
            for (pair<int, int> idx_pair : idx_pairs)
            {
                int next_y = idx_pair.first, next_x = idx_pair.second;
                if (seen.count({next_y, next_x}) == 0)
                {
                    queue.push_back({next_y, next_x});
                    // BFS 탐색을 수행해 나가면서, 현재 정점까지의 최단 경로 값을 갱신시켜 나간다. 
                    countQ.push_back(count + 1);
                    seen.insert({next_y, next_x});
                }
            }
        }
        return -1;
    }

private:
    int _rows, _cols;
    vector<vector<int>> _grid;

    // 현재 정점에서, 이동 가능한 경우만 골라 주는 함수 filter
    vector<pair<int, int>> filter(vector<pair<int, int>> idx_pairs)
    {
        vector<pair<int, int>> ret;
        for (pair<int, int> idx_pair : idx_pairs)
        {
            int y = idx_pair.first, x = idx_pair.second;
            if (y >= 0 && x >= 0 && this->_rows > y && this->_cols > x && this->_grid[y][x] == 0)
                ret.push_back({y, x});
        }
        return ret;
    }
};

int main()
{
    int row, col;
    cout << "(n X m) 형태의 인접 행렬에서, n, m 값을 입력해 주세요!" << "\n";
    cin >> row >> col;
    cout << "이제, 인접 행렬을 입력해 주세요!" << "\n";
    vector<vector<int>> matrix(row, vector<int>(col, 0));
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            cin >> matrix[i][j];
        }
    }
    ShortestPath shortcut;
    cout << "최단 거리: " << shortcut.BFS(matrix);
    return 0;
}