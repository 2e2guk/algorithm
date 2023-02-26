// 최대 곱 부분 수열 - dp
// array 가 주어지고, 주어진 array의 부분 수열 중에서, 원소들의 곱이 최대가 되는 부분 수열을 찾아서 최대 곱을 반환하는 함수를 작성해라. (최소 곱으로도 확장 가능)
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int maxProduct(vector<int>& nums) {

    // 현재 작업중인 부분 수열의 마지막 element가 반드시 포함된 부분 수열을 생각하자. 주의할 점은, 0이 주어지는 경우, 이전의 값이 어땠던 상관 없이 무조건 0이 되고,
    // 음수가 주어지는 경우, 이전의 값의 부호가 바뀐다는 점이다. 그래서, 현재 작업중인 부분 배열의 최대곱, 최소 곱을 모두 저장해서, 이전의 opt value를 포함하고, 현재 원소를 곱할 것인지, 
    // 아니면, 이전 opt value를 버리고 새로 시작할지 결정해야 한다. 

    // max_dp, min_dp 모두 nums의 첫 번째 원소로 초기화한다. 
    vector<int> max_dp(nums.size(), nums[0]); 
    vector<int> min_dp(nums.size(), nums[0]);

    // max_dp[n]  = max(min_dp[n - 1] * nums[n], max_dp[n - 1] * nums[n], nums[n])
    for (int i = 1; i < nums.size(); i++) {

        int cand0 = nums[i];
        int cand1 = max_dp[i - 1] * nums[i];
        int cand2 = min_dp[i - 1] * nums[i];

        int max_val = max({cand0, cand1, cand2});
        int min_val = min({cand0, cand1, cand2});

        max_dp[i] = max_val;
        min_dp[i] = min_val;
    }

    //  min_element()를 return 하게 하면 최소 곱으로도 확장 가능. 
    return *max_element(max_dp.begin(), max_dp.end());
}

int main() {
    int n;
    cout << "입력 배열의 크기를 입력해 주세요!" << "\n";
    cin >> n;
    vector<int> nums(n, 0);
    cout << "입력 배열을 입력해 주세요!" << "\n";
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }
    cout << maxProduct(nums) << endl;
    return 0;
}
