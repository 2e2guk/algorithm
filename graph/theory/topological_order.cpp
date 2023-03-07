// topological order(위상 정렬)
// 위상 정렬이란, DAG에서 각 정점들의 선행 순서를 위배하지 않고, 모든 정점을 나열하는 것이다.
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// 위상 정렬된 결과를 반환하는 함수. 
vector<int> topologicalOrder(const vector<vector<int>>& graph) {
    int vertex_num = graph.size();

    // 각 정점의 indegree를 저장하는 vector
    vector<int> indegs(vertex_num, 0);

    // 그래프의 각 정점이 가리키는 정점 index의, indegs값을 하나씩 더하며 update한다. 
    for (const auto& vertex : graph) {
        for (int to_idx : vertex) {
            indegs[to_idx]++;
        }
    }

    // indegree가 0인 정점들을 저장할 queue
    queue<int> deg0s;

    // update된 indegs에서, 0인 정점들을 queue에 push.
    for (int idx = 0; idx < vertex_num; ++idx) {
        if (indegs[idx] == 0) {
            deg0s.push(idx);
        }
    }

    // 위상 정렬의 결과를 저장할 topo_order
    vector<int> topo_order;

    while (!deg0s.empty()) {
        
        // queue.front() 를 pop한다. 
        int vtx0indeg = deg0s.front();
        deg0s.pop();
        topo_order.push_back(vtx0indeg);

        // vtx0indeg 가 가리키는 정점들의 indegree값을 -1해주며 update시킨다. 
        const vector<int>& vertex = graph[vtx0indeg];
        for (int to_idx : vertex) {
            indegs[to_idx]--;
            // update 하다가 indegree가 0이 되는 순간, deg0s 에 push한다. 
            if (indegs[to_idx] == 0) {
                deg0s.push(to_idx);
            }
        }
    }

    return topo_order;
}

int main() {
    int vertex_num;
    cout << "정점의 수를 입력해 주세요!" << "\n";
    cin >> vertex_num;
    // 입력 예시는 다음과 같다. 
    // vector<vector<int>> graph = {{1,3}, {2,5}, {}, {2}, {1}, {}};
    /*
                 4
                 |
                 |
                 v
        0 -----> 1 -----> 5
        |        | 
        |        | 
        v        v   
        3  ----> 2 
    */
   // graph의 각 원소들의 의미는, 각 index의 정점에서 출발해서 도착하는 정점을 나타낸다. 
   // 0번 정점에서, 1번, 3번 정점으로 이어지는 간선이 존재한다는 의미이다. 
    vector<vector<int>> graph(vertex_num);
    for (int i = 0; i < vertex_num; i++) {
        cout << i << "번 정점에서 출발하여 도착하는 정점들을 입력하세요 (-1을 입력하면 종료): ";
        int to_idx;

        // -1을 제외한 입력이 들어오는 동안, 반복한다. 
        while (cin >> to_idx) {
            if (to_idx == -1) break;
            graph[i].push_back(to_idx);
        }
    }
    vector<int> topo_order = topologicalOrder(graph);

    for (int idx : topo_order) {
        cout << idx << " ";
    }
    cout << endl;

    return 0;
}
