// 주어진 그래프를 깊은 복사하는 코드.
// 기본적으로, 주어진 그래프와 복제할 그래프의 vertex 사이의 mapping 관계를 만들어서, 복제할 그레프의 
// 정점들 사이의 연결 관게를 그대로 따 온다. 
#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>

using namespace std;

// vertex를 저장하는 Node class. 현재 vertex의 값과, 인접한 vertex들을 멤버 변수로 갖는다. 
class Node
{
public:
    int val;
    vector<Node *> neighbors;
    Node(int _val)
    {
        val = _val;
        neighbors = vector<Node *>();
    }
};

// Node *cloneGraph(Node *node) 함수는 그래프를 복사하는 함수이다.
// 입력으로 주어진 node 객체를 기준으로 그래프를 BFS(Breadth-First Search)를 통해 탐색하며, 
// 각 노드를 복사하여 새로운 노드 객체를 생성한다. 복사된 노드 객체들을 연결하여 새로운 그래프를 구성한다.
// 그리고, 새로 구성된 그래프의 첫 번째 노드인 node_map[node]를 반환한다.
Node *cloneGraph(Node *node)
{
    // 주어진 node객체가 nullptr인 경우.
    if (!node)
    {
        return nullptr;
    }
    unordered_map<Node *, Node *> hash;
    queue<Node *> q;
    q.push(node);

    // 기존의 node객체와, node->val 의 값을 갖는 새로운 노드 객체를 생성하고, 이 둘 사이에 mapping 관계를 만든다. 
    hash[node] = new Node(node->val);
    while (!q.empty())
    {
        auto n = q.front();
        q.pop();
        for (auto neighbor : n->neighbors)
        {
            if (hash.count(neighbor) == 0)
            {
                hash[neighbor] = new Node(neighbor->val);
                q.push(neighbor);
            }
            hash[n]->neighbors.push_back(hash[neighbor]);
        }
    }
    return hash[node];
}

int main()
{
    int n, m;
    cout << "정점의 개수와 간선의 개수를 순서대로 입력해 주세요: ";
    cin >> n >> m;
    vector<Node *> nodes(n);
    for (int i = 0; i < n; i++)
    {
        nodes[i] = new Node(i);
    }
    cout << "이제, 간선 정보를 입력해 주세요 (ex: 0-1인 경우 0 1 입력)" << "\n";
    for (int i = 0; i < m; i++)
    {
        int a, b;
        cin >> a >> b;
        nodes[a]->neighbors.push_back(nodes[b]);
        nodes[b]->neighbors.push_back(nodes[a]);
    }
    
    // 기존의 그래프를 deep copy해서 새로운 그래프 생성.
    auto cloned_graph = cloneGraph(nodes[0]);

    // 그리고, cloned_graph를 BFS 순회하면서, 인접한 정점들을 출력한다. 
    unordered_set<Node *> seen;
    queue<Node *> q;
    q.push(cloned_graph);
    seen.insert(cloned_graph);
    while (!q.empty())
    {
        auto node = q.front();
        q.pop();
        cout << node->val << ": ";
        for (auto neighbor : node->neighbors)
        {
            cout << neighbor->val << " ";
            if (seen.count(neighbor) == 0)
            {
                seen.insert(neighbor);
                q.push(neighbor);
            }
        }
        cout << endl;
    }
    return 0;
}