// lcs구현, lcs문자열의 길이와 lcs문자열까지 출력해 준다. 
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

// LCS의 길이와 LCS 문자열을 반환하는 함수. 
pair<int, string> longestCommonSubsequence(string text1, string text2) {

    // dp_table[i][j] 에는, text1의 i번째 index까지의 부분 문자열과, text2의 j번째 index까지의 부분 문자열 중, LCS의 길이가 저장된다. 
    vector<vector<int>> dp_table(text2.size() + 1, vector<int>(text1.size() + 1, 0));
    
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
    
    // LCS 문자열을 찾는 과정 - 마지막 문자열부터, 첫번째 문자열까지 이동한다. 
    int rowIdx = text2.size();
    int colIdx = text1.size();
    
    // lcs 문자열 초기화. 
    string lcs_str = "";
    while(rowIdx > 0 && colIdx > 0) {
        
        // text1, text2의 마지막 문자열이 서로 같은 경우, lcs에 문자를 추가한다.
        if(text2[rowIdx-1] == text1[colIdx - 1]) {
            lcs_str = text2[rowIdx - 1] + lcs_str;
            rowIdx--;
            colIdx--;
        } 
        
        // 마지막 문자열이 서로 같지 않은 경우, max에 의해 선택되는 쪽의 index를 감소시킨다. 
        else if(dp_table[rowIdx - 1][colIdx] > dp_table[rowIdx][colIdx - 1]) {
            rowIdx--;
        } else {
            colIdx--;
        }
    }

    return {dp_table[text2.size()][text1.size()], lcs_str};
}

int main() {
    string text1, text2;
    cout << "두 문자열을 입력해 주세요!" << "\n";
    cin >> text1 >> text2;
    pair<int, string> result = longestCommonSubsequence(text1, text2);
    cout << result.first << "\n";
    cout << result.second;
    return 0;
}

// 41-61까지 설명
// else if와 else문에서는 lcs에 문자를 추가하는 것이 아닌, 
// dp_table을 참조하여 lcs 문자열을 찾아가는 과정에서, 다음으로 이동할 위치를 결정하는 것이다.
// else if(dp_table[rowIdx - 1][colIdx] > dp_table[rowIdx][colIdx - 1]) { ... } 에서, 
// dp_table[rowIdx - 1][colIdx] > dp_table[rowIdx][colIdx - 1]은, 현재 위치에서 
// 위쪽 방향에 위치한 값이 왼쪽 방향에 위치한 값보다 크다는 것을 의미한다. 
// 이 경우, 위쪽 방향에 위치한 값이 현재 위치에서 선택될 가능성이 높다는 것을 의미하므로, 
// rowIdx값을 감소시켜서 위쪽 방향으로 이동한다.
// else문에서는 dp_table[rowIdx][colIdx - 1] > dp_table[rowIdx - 1][colIdx] 인 경우, 
// 현재 위치에서 왼쪽 방향에 위치한 값이 위쪽 방향에 위치한 값보다 크다는 것을 의미한다. 
// 이 경우, 왼쪽 방향에 위치한 값이 현재 위치에서 선택될 가능성이 높다는 것을 의미하므로, 
// colIdx값을 감소시켜서 왼쪽 방향으로 이동한다.
// 따라서, 이러한 과정을 반복하면,
// 마지막 문자열부터 첫번째 문자열까지 이동하면서, lcs 문자열을 찾아갈 수 있게 된다. 
