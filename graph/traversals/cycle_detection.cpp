// directed graph에서, cycle 을 찾는 코드. 
#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

class HasCycle {
public:
    // DFS탐색을 하며, 그래프에서의 cycle을 찾는 함수. 
    bool recurDFS(vector<vector<int>>& graph) {
        _graph = graph;
        for (int idx = 0; idx < graph.size(); ++idx) {

            // cycle-path. 현재 탐색중인 경로를 저장하며, 중복을 방지하기 위해서 hash_set인 unoedered_set을 이용해서 구현.
            unordered_set<int> loop_track;
            bool ret = _recurDFS(idx, loop_track);
            if (ret == true) {
                return true; // found a cycle
            }
        }
        return false;
    }

private:
    vector<vector<int>> _graph;

    // visited. 더 이상 탐색이 불가능한 경우에 해당 정점을 저장하는 hash-set. 중복을 방지하기 위해서 unordered_set으로 구현.
    unordered_set<int> _seen; 

    // 탐색 시작 위치 idx. 탐색 경로를 저장하는 hash_set loop_track.
    bool _recurDFS(int idx, unordered_set<int>& loop_track) {
        if (_seen.find(idx) != _seen.end()) { // 이미 방문한 경우.
            return false;
        }
        if (loop_track.find(idx) != loop_track.end()) { // cycle을 찾은 경우. 
            return true;
        }

        // 아직 현재 노드를 방문하지 않은 경우, _recurDFS를 재귀적으로 호출하며, 다음 노드를 방문한다. 
        // loop track에 현재 idx를 추가한다. 
        loop_track.insert(idx); 

        // 현재 정점에서 갈 수 있는 다음 정점들을 저장하는 nexts
        // ret은, 다음 노드를 방문하여 찾은 결과이다. 
        vector<int>& nexts = _graph[idx];
        for (int adj_idx : nexts) {
            bool ret = _recurDFS(adj_idx, loop_track);
            if (ret == true) {
                return true;
            }
        }

        // 현재 정점에서 갈 수 있는 정점들을 모두 탐색했으나, cycle을 찾지 못하고, 더 이상 탐색도 못 하는 경우 
        // backtrack 하고, loop_track에서 더 이상 탐색이 안 되는 정점을 지운다. 
        loop_track.erase(idx); 

        // 그리고 탐색이 더 이상 불가능한 정점은 visited처리한다. 
        _seen.insert(idx); 
        return false;
    }
};

int main() {
    HasCycle hasCycle;
    int vertex_num;
    cout << "정점의 수를 입력해 주세요!" << "\n";
    cin >> vertex_num;
    // vector<vector<int>> graph = {{1}, {}, {0}, {0, 4}, {1, 6}, {4}, {5}};
    // graph의 각 원소들의 의미는, 각 index의 정점에서 출발해서 도착하는 정점을 나타낸다. 
    // 3번 정점에서, 0번, 4번 정점으로 이어지는 간선이 존재한다는 의미이다. 
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
    bool ret = hasCycle.recurDFS(graph);
    cout << ret << endl;

    return 0;
}
