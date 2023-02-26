// 최장 길이 팰린드롬 부분 문자열 알고리즘에서 시간, 공간복잡도를 향상시킨 코드. 이 코드의 시간/공간 복잡도는 O(n)이다. 
// Manacher's algorithm 이용. 
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int longestPalindromeSize(string s) {
    int n = s.length();
    if (n == 0) return 0;

    // 입력 문자열에 새로운 문자를 삽입하여 문자열의 길이를 홀수로 만듦
    string t = "#";
    for (int i = 0; i < n; i++) {
        t += s[i];
        t += "#";
    }
    int m = t.length();

    vector<int> dp(m, 0);
    int max_len = 1, center = 0, right = 0;
    
    for (int i = 0; i < m; i++) {
        if (i <= right) {
            int j = center * 2 - i;
            dp[i] = min(right - i, dp[j]);
        }
        
        while (i - dp[i] - 1 >= 0 && i + dp[i] + 1 < m && t[i - dp[i] - 1] == t[i + dp[i] + 1]) {
            dp[i]++;
        }
        
        if (i + dp[i] > right) {
            center = i;
            right = i + dp[i];
        }
        
        if (dp[i] > max_len) {
            max_len = dp[i];
        }
    }
    
    return max_len;
}

int main() {
    string s;
    cin >> s;
    cout << longestPalindromeSize(s) << endl;
    return 0;
}