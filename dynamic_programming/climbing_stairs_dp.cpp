// 계단 오르기 문제. - dp로 해결
// n개의 계단을 오르는데, 한번에 1개 혹은 2개의 계단만 오를 수 있다. 이때, 총 몇 가지 방법으로 게단으로 오를 수 있을까?
#include <iostream>
#include <vector>

using namespace std;

// n번째 계단까지 올라가는데 걸리는 경우의 수를 구하는 함수. 
int climbStairs(int n, vector<int>& dp_array) {
    // 초기에 입력된 n 값이 입력으로 들어온 dp_array보다 작은 경우, 그냥 가지고 있는 값을 리턴한다. 
    if (n < dp_array.size()) { 
        return dp_array[n];
    }
    
    for (int i = 3; i <= n; i++) {
        // n번째 계단에 올라오는 방법은, n-1번째 계단에서 올라오거나, n-2번째 게단에서 올라오는 방법이 있다. 
        int ith_way = dp_array[i - 1] + dp_array[i - 2]; 
        dp_array.push_back(ith_way);
    }
    
    return dp_array[n];
}

int main() {
    int n;
    cout << "몇 개의 계단을 오르고 싶은지 입력해 주세요!" << "\n";
    cin >> n;
    vector<int> dp_array;
    dp_array.push_back(0);
    dp_array.push_back(1);
    dp_array.push_back(2);
    int ways = climbStairs(n, dp_array);
    cout << ways << " ways" << endl;
    return 0;
}
