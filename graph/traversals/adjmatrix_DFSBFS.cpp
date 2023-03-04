#include <iostream>
#include <vector>
#include <stack>
#include <queue>

using namespace std;

class graph_traversal {
public:
    // 인접 행렬로 표현된 그래프에서 DFS 수행 (재귀)
    void dfsMatrix(vector<vector<int>>& graph, int start) {
        vector<bool> visited(graph.size(), false);
        dfsMatrixHelper(graph, visited, start);
    }
    
    // 인접 행렬로 표현된 그래프에서 DFS 수행 (재귀 이용)
    void dfsMatrixHelper(vector<vector<int>>& graph, vector<bool>& visited, int cur) {
        visited[cur] = true;
        cout << cur << " ";
        for (int i = 0; i < graph.size(); i++) {
            if (graph[cur][i] != 0 && !visited[i]) {
                dfsMatrixHelper(graph, visited, i);
            }
        }
    }
    
    // 인접 행렬로 표현된 그래프에서 DFS 수행 (스택 이용)
    void dfsMatrixStack(vector<vector<int>>& graph, int start) {
        vector<bool> visited(graph.size(), false);
        stack<int> s;
        s.push(start);
        visited[start] = true;
        cout << start << " ";
        while (!s.empty()) {
            int cur = s.top();
            s.pop();
            for (int i = 0; i < graph.size(); i++) {
                if (graph[cur][i] != 0 && !visited[i]) {
                    s.push(i);
                    visited[i] = true;
                    cout << i << " ";
                }
            }
        }
    }

    // 인접 행렬로 표현된 그래프에서 BFS 수행
    void bfsMatrix(vector<vector<int>>& graph, int start) {
        vector<bool> visited(graph.size(), false);
        queue<int> q;
        q.push(start);
        visited[start] = true;
        cout << start << " ";
        while (!q.empty()) {
            int cur = q.front();
            q.pop();
            for (int i = 0; i < graph.size(); i++) {
                if (graph[cur][i] != 0 && !visited[i]) {
                    q.push(i);
                    visited[i] = true;
                    cout << i << " ";
                }
            }
        }
    }
};

int main() {
    // 인접 행렬로 그래프 생성
    int n;
    cout << "n X n 그래프의 n값을 입력해 주세요!" << "\n";
    cin >> n;
    vector<vector<int>> graph(n, vector<int>(n, 0));

    // 그래프를 인접 행렬 형태로 입력하기.
    cout << "그래프를 인접 행렬 형태로 입력해 주세요!" <<"\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> graph[i][j];
        }
    }

    graph_traversal gt;
    cout << "DFS (Recursive): ";
    gt.dfsMatrix(graph, 0); // DFS (Recursive)
    cout << endl;

    cout << "DFS (Stack): ";
    gt.dfsMatrixStack(graph, 0); // DFS (Stack)
    cout << endl;

    cout << "BFS: ";
    gt.bfsMatrix(graph, 0); // BFS
    cout << endl;

    return 0;
}
