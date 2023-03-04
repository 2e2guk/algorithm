// 연결 요소의 개수. 그래프가 에지 리스트 형태로 주어질 때, 주어진 그래프에서 연결 요소의 개수를 세어서 반환하는 함수 작성. 
#include <iostream>
#include <vector>
#include <unordered_set>
#include <stack>

using namespace std;

// 연결 요소의 개수를 반환하는 함수 작성.
int countComponents(int n, vector<vector<int>>& edges) {
    // 그래프 생성
    vector<vector<int>> vertices(n);
    for (auto& edge : edges) {
        // v0은 왼쪽 에지(시작 에지), v1은 오른쪽 에지(끝 에지)
        int v0 = edge[0], v1 = edge[1];
        vertices[v0].push_back(v1);
        vertices[v1].push_back(v0);
    }
    
    // 탐색 - unordered_set이용. undirected graph이므로 unordered_set 이용 가능. 
    unordered_set<int> visited;
    int comp_count = 0;
    for (int i = 0; i < n; i++) {
        if (visited.find(i) == visited.end()) {
            comp_count++;
            
            // DFS
            stack<int> s;
            s.push(i);
            visited.insert(i);
            
            while (!s.empty()) {
                int cur_idx = s.top();
                s.pop();
                for (int next_idx : vertices[cur_idx]) {
                    if (visited.find(next_idx) == visited.end()) {
                        visited.insert(next_idx);
                        s.push(next_idx);
                    }
                }
            }
        }
    }
    
    return comp_count;
}

int main() {
    cout << countComponents(6, {{0,1}, {1,2}, {2,0}, {3,4}}) << endl;
    return 0;
}
