// Lomgest Common Subsequence. - dp 로 해결. 
// lcs는, 두 문자열 중에서 가장 길이가 긴 공통 subsequence인데, subsequence는 subarray와는 다르게 구성 element들이 연속될 필요가 없다. 
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

// LCS의 길이를 반환하는 함수. 
int longestCommonSubsequence(string text1, string text2) {

    // dp_table[i][j] 에는, text1의 i번째 index까지의 부분 문자열과, text2의 j번째 index까지의 부분 문자열 중, LCS의 길이가 저장된다. 
    vector<vector<int>> dp_table(text2.size()+1, vector<int>(text1.size()+1, 0));
    
    for(int rowIdx = 1; rowIdx < dp_table.size(); rowIdx++) {
        int prev_row = rowIdx - 1;

        // char2는, text2의 마지막 문자열이다. 
        char char2 = text2[rowIdx - 1];
        for(int colIdx = 1; colIdx < dp_table[rowIdx].size(); colIdx++) {
            int prev_col = colIdx - 1;

            // char1은, text1의 마지막 문자열이다. 
            char char1 = text1[colIdx - 1];

            int dp = 0;
            // problem/subproblem으로 나누는 과정에서, 만약, text1의 마지막 문자열과, text2의 마지막 문자열이 같다면, 
            // 그 같은 문자열을 LCS로 빼고, LCS길이에 1을 더해 준다(3가지 subproblem이 있지만, 결국 max값으로 이 경우가 선택됨)
            if(char1 == char2) {
                dp = dp_table[prev_row][prev_col] + 1;
            } else {

                // 그렇지 않은 경우, dp_table[prev_row][prev_col] + 1의 경우는 선택이 될 수가 없다. 고로, text1의 부분 문자열의 마지막 경우만 뺀 것과,
                // text2의 부분 문자열의 마지막 경우만 뺀 것 중에서 max값을 취한다. 
                dp = max(dp_table[prev_row][colIdx], dp_table[rowIdx][prev_col]);
            }
            dp_table[rowIdx][colIdx] = dp;
        }
    }
    
    return dp_table[text2.size()][text1.size()];
}

int main() {
    string text1, text2;
    cout << "두 문자열을 입력해 주세요!" << "\n";
    cin >> text1 >> text2;
    cout << longestCommonSubsequence(text1, text2) << endl;
    return 0;
}
