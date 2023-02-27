// 0-1 knapsack problem - bottom_up 방식으로 구현.
// 여기서는, 최대 가치만 출력하도록 구현.
#include <iostream>
#include <vector>

using namespace std;

class ObjectVal {
public:
    int weight;
    int value;

    // initializer
    ObjectVal(int w, int v) {
        weight = w;
        value = v;
    }
};

class KnapSack {
private:
    vector<ObjectVal> _objects;
    vector<vector<int>> _dp;

    // dp table은, 물건들과 무게 제한에 따른, 각각의 경우의 조건을 만족시키는 최대 이익을 저장한다. 
    // dp table 을 생성하고, dp table을 초기화하는 함수. 0번 row와, 0번 col의 값은 모두 0이다.
    // 물건을 아예 선택하지 않거나(row = 0), 무게 제한이 0인 경우이다(col = 0).
    void _initDPTable(int object_count, int weight_limit) {

        // 비어있는 dp table 생성. 
        _dp = vector<vector<int>>(object_count + 1, vector<int>(weight_limit + 1));
        for (int rowIdx = 0; rowIdx < _dp.size(); rowIdx++) {
            _dp[rowIdx][0] = 0;
        }

        for (int colIdx = 0; colIdx < weight_limit + 1; colIdx++) {
            _dp[0][colIdx] = 0;
        }
    }

public:
    KnapSack(vector<ObjectVal> objects) {
        _objects = objects;
    }

    // bottom-up 방식으로 0-1 kanpsack problem 을 구현한 코드. 
    int bottomUp(int weight_limit) {

        // 물건들의 개수를 나타내는 obj_endIdx와 dp table을 초기화한다.
        int obj_endIdx = _objects.size();
        _initDPTable(obj_endIdx, weight_limit);

        // dp_table[n][W] = max(dp_table[n - 1][W - w[n]] + val[n], dp_table[n - 1][W] + 0) 
        // 기본적으로, problem/subproblem 으로 쪼갤 때 "특정 물건이 포함된다/포함되지 않는다" 라는 기준으로 나누어야 한다.
        // 그러면, 특정 물건을 제외한 opt value를 구해야 하는 것이다. 
        // 전자는 특정 물건이 배낭에 이미 존재하는 경우. 그 경우는, 그 물건을 제외한 opt value에 그 물건의 가치를 더한다. 
        // 후자는, 특정 물건이 배낭에 존재하지 않는 경우이다. 물건이 없으니 무게 제한도 바뀌지 않는다. 더해지는 물건의 가치도 없다. 
        // 전자와 후자 중 더 큰 값을 취하며 dp table을 완성시켜 나간다. 
        for (int rowIdx = 1; rowIdx < _dp.size(); rowIdx++) {
            for (int colIdx = 1; colIdx < weight_limit + 1; colIdx++) {

                // dp_table[n - 1][W] + 0 의 경우이다. 특정 물건을 제외하고 생각하므로 n - 1이고, 
                // 무게 제한은 바뀌지 않으므로 그대로 W, 물건의 가치는 물건이 없으니 더해지지 않는다. 
                int prev_obj_idx = rowIdx - 1;
                int not_taking_val = _dp[prev_obj_idx][colIdx];

                // dp_table[n - 1][W - w[n]] + val[n] 의 경우이다. 특정 물건이 배낭에 존재하므로, 해당 특정 물건의 무게를
                // 원래 무게 제한에서 빼 줘야 한다. 그리고 특정 물건의 가치를 더해 줘야 한다. 
                // 이 물건을 제외하고 생각하는 것이므로 n - 1이 된다.
                int weight = _objects[rowIdx - 1].weight;
                int value = _objects[rowIdx - 1].value;
                int taking_val = 0;

                // W - w[n]
                int prev_weight_limit = colIdx - weight;
                // 만약, 배낭의 무게 제한이 음수가 되는 경우, invalid한 경우이므로 0이 된다.(고려하지 않는다)
                if (prev_weight_limit < 0) {
                    taking_val = 0;
                } else {
                    // dp_table[n - 1][W - w[n]] + val[n]
                    taking_val = _dp[prev_obj_idx][prev_weight_limit] + value;
                }

                // 특정 물건이 존재하는 경우, 존재하지 않는 경우의 가치 중, 더 큰 값을 반환해 준다. 
                int max_val = max(not_taking_val, taking_val);
                _dp[rowIdx][colIdx] = max_val;
            }
        }

        return _dp[obj_endIdx][weight_limit];
    }
};
int main() {
    int nums = 0;
    vector<ObjectVal> objects;
    cout << "물건의 종류의 수를 입력해 주세요!" << "\n";
    cin >> nums;
    cout << "물건의 무게와 가치를 순서대로 입력해 주세요!" << "\n";
    for (int i = 0; i < nums; i++) {
        int weight, value;
        cin >> weight >> value;
        objects.push_back({weight, value});
    }
    KnapSack knapsack(objects);

    int weight_limit;
    cout << "배낭의 무게 제한을 입력해 주세요!" << "\n";
    cin >> weight_limit;
    
    cout << "Bottom-up approach: " << knapsack.bottomUp(weight_limit) << endl;
    
    return 0;
}
