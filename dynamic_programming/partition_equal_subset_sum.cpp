// 합이 같은 두 집합으로 나누기. - 0-1 knapsack problem 문제의 변형. 결국 각 원소를 선택할지/선택하지 않을지가 관건이다. 
// 입력으로 집합이 주어질 때, 해당 집합을 합이 같은 두 subset으로 분류가 가능한지 판별하라. 

#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

// 주어진 집합을 합이 동일한 두 부분집합으로 나눌 수 있는지 여부를 출력하는 함수. 
bool canPartition(vector<int>& nums) {
    int total = accumulate(nums.begin(), nums.end(), 0);  // 0으로 초기화
    
    // total 값이 짝수가 아닌 경우, 무조건 false이다. 
    if(total % 2 == 1) {
        return false;
    }
    
    int half_sum = total / 2;
    
    // dp_table[i][j] 에는, i번째 숫자까지를 사용하여 j라는 합을 만들어 낼 수 있는지에 대한 bool값이 주어진다. 
    vector<vector<bool>> dp_table(nums.size() + 1, vector<bool>(half_sum + 1, false));
    
    // dp[i][0]은 항상 true이다. 합 0을 만들기 위해선 모든 원소들을 간단히 선택하지 않으면 된다.
    for(int rowIdx = 0; rowIdx < dp_table.size(); rowIdx++) {
        dp_table[rowIdx][0] = true;
    }
    
    // dp(n, s) = dp(n-1, s-nums[n]) || dp(n-1, s)
    for(int rowIdx = 1; rowIdx < dp_table.size(); rowIdx++) {

        // row에 0번째 index로 공집합을 추가했으므로, 진짜 첫 번째 원소를 추출하기 위해선 -1을 해 준다.
        int nth_num = nums[rowIdx - 1];
        int prev_row = rowIdx - 1;

        for(int colIdx = 1; colIdx < dp_table[rowIdx].size(); colIdx++) {
            bool dp0 = false;

            // s-nums[n] = prev_col
            int prev_col = colIdx - nth_num;
            if(0 <= prev_col) {
                // dp0 = 특정 원소가 포함된다고 계산했을 때의 dp값.(dp(n, s - nums[n]))
                dp0 = dp_table[prev_row][prev_col];
            }
            // dp1 = 특정 원소가 포함되지 않는다고 계산했을 때의 dp값. 
            bool dp1 = dp_table[prev_row][colIdx];
            
            // 왜 or연산인가? - dp0은 특정 원소를 선택해서, 'sum - 특정 원소의 값' 을 만들 수 있는지를 나타내고, 
            // dp1은, 특정 원소를 선택하지 않고 j를 만들 수 있는지를 나태낸다. 그러면, 두 경우 중 하나라도 참이면, 
            // i개의 원소로 j를 만들 수 있으므로, dp_table[i][j] 는 true이다. 
            bool dp = dp0 || dp1;
            dp_table[rowIdx][colIdx] = dp;
        }
    }
    
    return dp_table[nums.size()][half_sum];
}

int main() {
    int element_num;
    cout << "입력하고자 하는 집합의 원소의 개수를 입력해 주세요!" << "\n";
    cin >> element_num;
    vector<int> nums(element_num, 0);
    cout << "입력하고자 하는 집합을 입력해 주세요!" << "\n";
    for (int i = 0; i < element_num; i++) {
        cin >> nums[i];
    }
    cout << std::boolalpha << canPartition(nums) << endl;
    return 0;
}
