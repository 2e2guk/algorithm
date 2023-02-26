// 최대 합 부분 수열 문제 - dp로 해결. (kadane's algorithm)
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// 입력받은 nums 배열에 대해서, 부분 합이 최대가 되는 부분 수열의 합을 출력하는 함수. 
int maxSubArray(vector<int>& nums) {

    // 입력받은 배열에 원소가 없는 경우, 0을 반환.
    if (nums.size() == 0) {
        return 0;
    }
    
    // 입력받은 배열의 원소 수가 1개인 경우, 해당 원소의 값을 반환.
    if (nums.size() == 1) {
        return nums[0];
    }
    
    // 그렇지 않은 경우, 최대 합 부분 수열을 bottom-up 방식으로 구한다. dp_array는, 처음 ~ 현재 인덱스까지의 부분 수열에서 최대 합을 저장한다. 
    vector<int> dp_array(nums.size(), 0);

    // dp_array[0] 은 nums[0]으로 초기화한다. 
    dp_array[0] = nums[0]; 
    
    for (int idx = 1; idx < nums.size(); ++idx) {
        int prev_max = dp_array[idx - 1];
        int crnt_val = nums[idx];
        
        int connected_sum = prev_max + crnt_val;
        // 처음부터, 현재 idx 까지의 부분 수열 중에서, 마지막 원소가 반드시 포함된다고 가정하자. 그러면 
        // max(이전 opt value + 마지막 원소, 마지막 원소) 가 dp_array[idx]의 값이 된다. (이전 opt value = dp[idx - 1]의 값)
        int max_sub = max(connected_sum, crnt_val);
        dp_array[idx] = max_sub;
    }
    
    // dp_array에서 최댓값을 찾아주면, 그것이 최대 부분 수열의 합이 된다. 
    int max_sum = *max_element(dp_array.begin(), dp_array.end());
    return max_sum;
}

int main() {
    int element_num;
    cout << "array에 원소가 몇 개 있는지 입력해 주세요: " <<"\n";
    cin >> element_num;
    vector<int> nums(element_num, 0);
    cout << "이제 입력 array를 입력해 주세요!" << "\n"; 
    for (int i = 0; i < element_num; i++) {
        cin >> nums[i];
    }
    cout << maxSubArray(nums) << endl;
    return 0;
}
