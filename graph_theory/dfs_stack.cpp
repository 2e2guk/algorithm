// dfs를 스택으로 구현한 함수. 
#include <iostream>
#include <stack>
#include <vector>

using namespace std;

vector<int> dfs(const vector<vector<int>>& adj_list, int start, stack<int> stk) {
    vector<bool> visited(adj_list.size(), false);
    vector<int> visit_order;

    while (!stk.empty()) {
        int current_vertex = stk.top();
        stk.pop();

        if (visited[current_vertex]) continue;

        visited[current_vertex] = true;
        visit_order.push_back(current_vertex);

        for (int v : adj_list[current_vertex]) {
            if(!visited[v]) 
                stk.push(v);
        }
        return visit_order;
    }

}