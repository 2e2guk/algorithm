// dfs를 재귀를 이용하여 구현. 
#include <iostream>
#include <vector>

using namespace std;

const int N = 6; // 그래프의 정점 개수. 
bool gVisited[N] = {};

void dfs_recursion(const vector<vector<int>>& adj_list, int s) {
    if(gVisited[s]) return;

    gVisited[s] = true;
    cout << s << endl;

    for(int v : adj_list[s])
        dfs_recursion(adj_list, v);
}
