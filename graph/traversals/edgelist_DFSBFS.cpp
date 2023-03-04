// 에지 리스트로 그래프가 주어졌을 때, DFS/BFS 를 수행하는 코드. 
#include <iostream>
#include <vector>
#include <stack>
#include <queue>

using namespace std;

class graph_traversal {
public:
    // 에지 리스트로 표현된 그래프에서 DFS 수행 (재귀)
    void dfsEdge(vector<pair<int, int>>& graph, int start) {
        vector<bool> visited(graph.size(), false);
        dfsEdgeHelper(graph, visited, start);
    }

    // 에지 리스트로 표현된 그래프에서 DFS 수행 (재귀 이용)
    void dfsEdgeHelper(vector<pair<int, int>>& graph, vector<bool>& visited, int cur) {
        visited[cur] = true;
        cout << cur << " ";
        for (int i = 0; i < graph.size(); i++) {
            int u = graph[i].first;
            int v = graph[i].second;
            if (u == cur && !visited[v]) {
                dfsEdgeHelper(graph, visited, v);
            }
        }
    }

    // 에지 리스트로 표현된 그래프에서 DFS 수행 (스택 이용)
    void dfsEdgeStack(vector<pair<int, int>>& graph, int start) {
        vector<bool> visited(graph.size(), false);
        stack<int> s;
        s.push(start);
        visited[start] = true;
        cout << start << " ";
        while (!s.empty()) {
            int cur = s.top();
            s.pop();
            for (int i = 0; i < graph.size(); i++) {
                int u = graph[i].first;
                int v = graph[i].second;
                if (u == cur && !visited[v]) {
                    s.push(v);
                    visited[v] = true;
                    cout << v << " ";
                }
            }
        }
    }

    // 에지 리스트로 표현된 그래프에서 BFS 수행
    void bfsEdge(vector<pair<int, int>>& graph, int start) {
        vector<bool> visited(graph.size(), false);
        queue<int> q;
        q.push(start);
        visited[start] = true;
        cout << start << " ";
        while (!q.empty()) {
            int cur = q.front();
            q.pop();
            for (int i = 0; i < graph.size(); i++) {
                int u = graph[i].first;
                int v = graph[i].second;
                if (u == cur && !visited[v]) {
                    q.push(v);
                    visited[v] = true;
                    cout << v << " ";
                }
            }
        }
    }
};

int main() {
    // 에지 리스트로 그래프 생성
    int n;
    cout << "에지 수를 입력해 주세요: ";
    cin >> n;
    vector<pair<int, int>> graph(n);

    // 그래프를 에지 리스트 형태로 입력하기.
    cout << "그래프를 에지 리스트 형태로 입력해 주세요!" <<"\n";
    for (int i = 0; i < n; i++) {
        cout << i << "번 에지의 출발점과 도착점을 입력해주세요: ";
        int u, v;
        cin >> u >> v;
        graph[i] = {u, v};
    }

     graph_traversal gt;
    cout << "DFS (Recursive): ";
    gt.dfsEdge(graph, 0); // DFS (Recursive)
    cout << endl;

    cout << "DFS (Stack): ";
    gt.dfsEdgeStack(graph, 0); // DFS (Stack)
    cout << endl;

    cout << "BFS: ";
    gt.bfsEdge(graph, 0); // BFS
    cout << endl;

    return 0;
}
