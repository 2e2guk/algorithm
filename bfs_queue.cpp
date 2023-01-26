// bfs 구현 코드. 큐를 이용하여 구현하였다. 
#include <iostream> 
#include <queue>
#include <vector>

using namespace std;

vector<int> bfs(const vector<vector<int>>& adj_list, int start) {
    vector<bool> visited(adj_list.size(), false);
    vector<int> visit_order;
    queue<int> q;
    q.push(s);

    while (!q.empty()) {
        int current_vertex = q.front();
        q.pop();

        if (visited[current_vertex]) continue;

        visited[current_vertex] = true;
        visit_order.push_back(current_vertex); // 이 부분에 정점 방문 시 원하는 작업이 있다면 작성한다. 

        for (int v : adj_list[current_vertex]) {
            if(!visited[v]) 
                q.push(v);
        }
        return visit_order;
    }

}