// 인접 리스트 형태로 그래프가 주어졌을 때, DFS/BFS를 수행하는 코드
#include <iostream>
#include <vector>
#include <stack>
#include <queue>

using namespace std;

class graph_traversal {
public:
    // 인접 리스트로 표현된 그래프에서 DFS 수행 (재귀)
    void dfsList(vector<vector<int>>& graph, int start) {
        vector<bool> visited(graph.size(), false);
        dfsListHelper(graph, visited, start);
    }
    
    // 인접 리스트로 표현된 그래프에서 DFS 수행 (재귀 이용)
    void dfsListHelper(vector<vector<int>>& graph, vector<bool>& visited, int cur) {
        visited[cur] = true;
        cout << cur << " ";
        for (int i = 0; i < graph[cur].size(); i++) {
            int next = graph[cur][i];
            if (!visited[next]) {
                dfsListHelper(graph, visited, next);
            }
        }
    }
    
    // 인접 리스트로 표현된 그래프에서 DFS 수행 (스택 이용)
    void dfsListStack(vector<vector<int>>& graph, int start) {
        vector<bool> visited(graph.size(), false);
        stack<int> s;
        s.push(start);
        visited[start] = true;
        cout << start << " ";
        while (!s.empty()) {
            int cur = s.top();
            s.pop();
            for (int i = 0; i < graph[cur].size(); i++) {
                int next = graph[cur][i];
                if (!visited[next]) {
                    s.push(next);
                    visited[next] = true;
                    cout << next << " ";
                }
            }
        }
    }

    // 인접 리스트로 표현된 그래프에서 BFS 수행
    void bfsList(vector<vector<int>>& graph, int start) {
        vector<bool> visited(graph.size(), false);
        queue<int> q;
        q.push(start);
        visited[start] = true;
        cout << start << " ";
        while (!q.empty()) {
            int cur = q.front();
            q.pop();
            for (int i = 0; i < graph[cur].size(); i++) {
                int next = graph[cur][i];
                if (!visited[next]) {
                    q.push(next);
                    visited[next] = true;
                    cout << next << " ";
                }
            }
        }
    }
};

int main() {
    // 인접 리스트로 그래프 생성
    int n;
    cout << "노드 수를 입력해 주세요: ";
    cin >> n;
    vector<vector<int>> graph(n);

    // 그래프를 인접 리스트 형태로 입력하기.
    cout << "그래프를 인접 리스트 형태로 입력해 주세요!" <<"\n";
    for (int i = 0; i < n; i++) {
        cout << i << "번 노드와 연결된 노드들을 입력해주세요: ";
        int m;
        cin >> m;
        for (int j = 0; j < m; j++) {
            int node;
            cin >> node;
            graph[i].push_back(node);
        }
    }

    graph_traversal gt;
    cout << "DFS (Recursive): ";
    gt.dfsList(graph, 0); // DFS (Recursive)
    cout << endl;

    cout << "DFS (Stack): ";
    gt.dfsListStack(graph, 0); // DFS (Stack)
    cout << endl;

    cout << "BFS: ";
    gt.bfsList(graph, 0); // BFS
    cout << endl;

    return 0;
}
    