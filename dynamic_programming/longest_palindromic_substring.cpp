// 최장 길이 팰린드롬 부분 문자열 구하기. 
// 문자열이 주어질 때, 이 문자열의 팰린드롬 문자열(순서대로 읽어도, 역순으로 읽어도 똑같은 문자열)을 구하라. 
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// 주어진 문자열에서 최장 길이 팰린드롬 문자열을 반환하는 함수. 
string longestPalindrome(string s) {
    int str_length = s.length();

    // dp_table[i][j]는 문자열 s의 i번째부터 j번째까지의 부분 문자열이 팰린드롬인지 아닌지를 나타내며, 팰린드롬이라면 그 부분 문자열의 길이를 저장한다. 
    vector<vector<int>> dp_table(str_length, vector<int>(str_length, 0));
    
    // (i, i) 위치의 dp_table 값은 1이다. 
    for(int i = 0; i < str_length; i++) {
        dp_table[i][i] = 1;
    }
    
    // 입력 문자열 s에서, s[i]와 s[i + 1]이 동일한 경우, dp_table[i][i + 2]를 2로 설정한다. 
    // 이는 문자열 s의 i번째와 i + 1번째 문자가 서로 같은 경우, 이 부분 문자열 자체가 팰린드롬이 되기 때문이다. 
    for(int i = 0; i < str_length - 1; i++) {
        if(s[i] == s[i + 1]) {
            dp_table[i][i + 1] = 2;
        }
    }
    
    // 이제 길이가 3 이상인 부분 문자열에 대해 살펴보자. (31번째 줄의  for문이 돌아가기 위해서는 str_length값이 3 이상이어야 한다.)
    for(int k = 2; k < str_length; k++) {
        for(int i = 0; i < str_length - k; i++) {
            int j = i + k;
            // [i]부터 s[j]까지의 부분 문자열이 팰린드롬이면, s[i+1]부터 s[j-1]까지의 부분 문자열도 팰린드롬이기 때문에, dp_table[i][j] = dp_table[i + 1][j - 1] + 2이다. 
            if(s[i] == s[j] && dp_table[i + 1][j - 1] != 0) {
                dp_table[i][j] = dp_table[i + 1][j - 1] + 2;
            }
        }
    }
    
    // dp_table을 모두 채우고, dp_table 에서 최댓값을 찾는다. 
    int max_length = 0, start_idx = 0, end_idx = 0;
    for(int i = 0; i < str_length; i++) {
        for(int j = i; j < str_length; j++) {
            int cur_length = dp_table[i][j];
            if(cur_length > max_length) {
                max_length = cur_length;
                start_idx = i;
                end_idx = j;
            }
        }
    }
    
    // string::substr() 함수는 첫 번째 인자로 시작하는 인덱스를, 두 번째 인자로는 길이를 인자로 받는다. 그래서, [start_idx, end_idx]의 길이를 두 번째 인자로 전달한다. 
    string sub_str = s.substr(start_idx, end_idx - start_idx + 1);
    return sub_str;
}

int main() {
    string s;
    cout << "input 문자열을 입력해 주세요: " << "\n";
    cin >> s;
    cout << longestPalindrome(s) << endl;
    return 0;
}
