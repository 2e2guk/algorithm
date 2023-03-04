// 그래프가 에지 리스트로 주어질 때, DFS/BFS를 수행하는 코드. vector<bool> visited 대신, unordered_set 사용. 
// unordered_set을 사용하는 경우, 원소들의 검색/삽입/삭제 시간인 O(1) 로, vector의 O(n)보다 훨씬 빠르다. 
// 이는 그래프 탐색 속도를 크게 개선시킨다(입력 그래프의 크기가 커지면 커질수록 더)
// 적용할 수 있는 그래프는, 1. undirected graph 2. directed acyclic graph(DAG). 
// 1 의 경우는, visited 배열 대신에 unordered_set을 이용해야 하기 때문에 추가적인 메모리를 사용해야 한다는 단점이 있다.
#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <unordered_set>

using namespace std;

class graph_traversal {
public:
    // 에지 리스트로 표현된 그래프에서 DFS 수행 (재귀)
    void dfsEdge(vector<pair<int, int>>& graph, int start) {
        unordered_set<int> visited;
        dfsEdgeHelper(graph, visited, start);
    }

    // 에지 리스트로 표현된 그래프에서 DFS 수행 (재귀 이용)
    void dfsEdgeHelper(vector<pair<int, int>>& graph, unordered_set<int>& visited, int cur) {
        visited.insert(cur);
        cout << cur << " ";
        for (int i = 0; i < graph.size(); i++) {
            int u = graph[i].first;
            int v = graph[i].second;
            if (u == cur && visited.find(v) == visited.end()) {
                dfsEdgeHelper(graph, visited, v);
            }
        }
    }

    // 에지 리스트로 표현된 그래프에서 DFS 수행 (스택 이용)
    void dfsEdgeStack(vector<pair<int, int>>& graph, int start) {
        unordered_set<int> visited;
        stack<int> s;
        s.push(start);
        visited.insert(start);
        cout << start << " ";
        while (!s.empty()) {
            int cur = s.top();
            s.pop();
            for (int i = 0; i < graph.size(); i++) {
                int u = graph[i].first;
                int v = graph[i].second;
                if (u == cur && visited.find(v) == visited.end()) {
                    s.push(v);
                    visited.insert(v);
                    cout << v << " ";
                }
            }
        }
    }

    // 에지 리스트로 표현된 그래프에서 BFS 수행
    void bfsEdge(vector<pair<int, int>>& graph, int start) {
        unordered_set<int> visited;
        queue<int> q;
        q.push(start);
        visited.insert(start);
        cout << start << " ";
        while (!q.empty()) {
            int cur = q.front();
            q.pop();
            for (int i = 0; i < graph.size(); i++) {
                int u = graph[i].first;
                int v = graph[i].second;
                if (u == cur && visited.find(v) == visited.end()) {
                    q.push(v);
                    visited.insert(v);
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

