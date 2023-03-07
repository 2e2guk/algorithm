// 입력으로 주어지는 그래프가 이분 그래프인지 판별하는 코드. 
// 그래프는 인접 리스트 형태로 주어짐.
#include <iostream>
#include <vector>
#include <stack>
#include <unordered_set>

using namespace std;

bool isBipartiteDFS(const vector<vector<int>>& graph) {
    int vertex_num = graph.size();
    // 0 : 채색되지 않은 상태, 1 : GroupA, -1 : GroupB 
    vector<int> colors(vertex_num, 0);

    // 방문한 정점을 저장하는 unordered_set. 현재 그래프는 undirected graph이므로, unordered_set 사용 가능. 
    // unordered_set을 사용하면, 중복 처리를 막을 수 있어서 방문했던 정점들을 다시 방문하는 일이 없어진다. 
    // 일반적인 경우, vector 를 사용한다.
    unordered_set<int> seen;
    
    for (int start_idx = 0; start_idx < vertex_num; ++start_idx) {
        
        // seen에, start_idx의 키를 가진 값이 있다면(start_idx를 이미 방문했다면), continue
        if (seen.count(start_idx)) {
            continue;
        }
        
        stack<int> st;
        st.push(start_idx);
        seen.insert(start_idx);
        // 시작 정점을 채색한다. 
        colors[start_idx] = 1;
        
        while (!st.empty()) {
            int idx = st.top();
            st.pop();

            // 현재 정점과 인접한 정점들의 index를 저장하는 conn_idxs.
            const vector<int>& conn_idxs = graph[idx];
            
            // 현재 정점의 색깔. 
            int color = colors[idx];
            
            for (int conn_idx : conn_idxs) {

                // 아직 방문하지 않은 정점이라면, seen, stack에 삽입하고,
                // 해당 정점의 색을 현재 정점의 색과 반대로 채색한다. 
                if (!seen.count(conn_idx)) {
                    seen.insert(conn_idx);
                    st.push(conn_idx);
                    colors[conn_idx] = -1 * color;
                    continue;
                }
                // 이미 방문한 정점인 경우. 
                // 현재 정점과 인접한 정점들에 칠한 색이 현재 정점의 색과 같은 경우
                // false 반환. 
                if (colors[conn_idx] * color != -1) {
                    return false;
                }
            }
        }
    }
    
    return true;
}

int main() {
    int vertex_num, edge_num;
    cin >> vertex_num >> edge_num;
    
    vector<vector<int>> graph(vertex_num);
    
    // 여기서는 정점이 0부터 시작한다고 가정했지만, 만약에 정점이 1부터 시작한다면, 
    // 아래 for문 그래프에 삽입할 때, from - 1, to - 1 을 해 줘야 한다. 
    for (int i = 0; i < edge_num; ++i) {
        int from, to;
        cin >> from >> to;
        graph[from].push_back(to);
        graph[to].push_back(from);
    }
    
    cout << boolalpha << isBipartiteDFS(graph) << endl;
    
    return 0;
}
