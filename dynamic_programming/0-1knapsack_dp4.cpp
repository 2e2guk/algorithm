// 0-1 knapsack problem - bottom_up 방식으로 구현.
#include <iostream>
#include <vector>

using namespace std;

class ObjectVal {
public:
    int weight;
    int value;

    ObjectVal(int w, int v) {
        weight = w;
        value = v;
    }
};

class KnapSack {
private:
    vector<ObjectVal> _objects;
    vector<vector<int>> _dp;

    void _initDPTable(int object_count, int weight_limit) {
        _dp = vector<vector<int>>(object_count+1, vector<int>(weight_limit+1));
        for (int rowIdx = 0; rowIdx < _dp.size(); rowIdx++) {
            _dp[rowIdx][0] = 0;
        }

        for (int colIdx = 0; colIdx < weight_limit+1; colIdx++) {
            _dp[0][colIdx] = 0;
        }
    }

public:
    KnapSack(vector<ObjectVal> objects) {
        _objects = objects;
    }

    int bottomUp(int weight_limit) {
        int obj_endIdx = _objects.size();
        _initDPTable(obj_endIdx, weight_limit);

        for (int rowIdx = 1; rowIdx < _dp.size(); rowIdx++) {
            for (int colIdx = 1; colIdx < weight_limit+1; colIdx++) {
                int prev_obj_idx = rowIdx - 1;
                int not_taking_val = _dp[prev_obj_idx][colIdx];

                int weight = _objects[rowIdx-1].weight;
                int value = _objects[rowIdx-1].value;

                int taking_val = 0;
                int prev_weight_limit = colIdx-weight;
                if (prev_weight_limit < 0) {
                    taking_val = 0;
                } else {
                    taking_val = _dp[prev_obj_idx][prev_weight_limit] + value;
                }

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