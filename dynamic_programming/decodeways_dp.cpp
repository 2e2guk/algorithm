// decode ways - dp
// A - 1, B - 2, C - 3 , ... , Z - 26 으로 인코딩된 숫자 암호가 있다. 이를 디코딩 할 수 있는 방법의 수를 구하라. 
#include <iostream>
#include <vector>
#include <string>

using namespace std;

// 인코딩된 문자열을 받아서, 이 문자열이 몇 가지 방법으로 디코딩될 수 있는지를 출력하는 함수. 
int decodingBtmUp(string s) {

    int str_length = s.length();

    // 입력된 문자열이 없어서, 암호로 해석할 수 없는 경우.
    if (str_length == 0) {
        return 0;
    }
    // 입력받은 암호 문자열과 일대일로 대응되는 dp라는 vector.
    // vector의 각 요소는 해당 index에 대응되는 문자열의 원소부터, 끝까지, 가능한 해석 방법의 수가 저장된다. 
    vector<int> dp(str_length + 1, 0);

    // dp[str_length] = 1은, 문자열을 맨 뒤부터 처리하기 위한 코드이다. 길이가 str_length인 암호를 해석하는 방법의 수를 1로 초기화하는 것이다. 
    dp[str_length] = 1;


    // last_char에는, 입력된 암호의 마지막 문자가 저장된다. 
    char last_char = s[str_length - 1];
    
    // 마지막 문자가 0인 경우, 해석할 수 없는 경우이므로 0 저장, 그렇지 않은 경우 1 저장.(한 자리 수이므로 0이 아니라면 무조건 해석가능).
    if (last_char == '0') {
        dp[str_length - 1] = 0;
    } else {
        dp[str_length - 1] = 1;
    }

    // 문자열의 마지막 문자 직전 문자부터, 문자열의 첫 번째 문자까지 진행한다. 
    for (int idx = str_length - 2; idx >= 0; --idx) {
        // single_num에는, 입력 문자열의 idx에 해당하는 문자를 숫자로 바꾼다. 
        // '0'은 아스키 코드에서 0에 해당하는 값으로, 문자열에서 '0'을 빼게 되면, 해당 문자에 해당하는 정수 값이 나온다.
        int single_num = s[idx] - '0';
        int single_count = 0;

        // 44 - 59 번째 줄은, 주어진 문자열을,  (맨뒤 1개/나머지), (맨뒤 2개/나머지) 로 나누어서 각각의 디코딩 방법의 수를 더해서 idx에서 디코딩 방법의 수인 count를 완성한다. 
        // single_num은 한자리 수로, 0이 아니라면 무조건 해석이 가능하다. 그러면 아까 초기화했던  dp[str_length - 1] = 1의 값을 그대로 사용한다. 
        if (0 < single_num) {
            single_count = dp[idx + 1];
        }

        // double_num은 두 자리 수로, 디코딩 가능한 범위 내에 있는 경우에, double_count값을 맨처음 초기화했던 dp[str_length] = 1 값을 사용해 설정한다. 
        int double_num = stoi(s.substr(idx, 2));
        int double_count = 0;
        if (10 <= double_num && double_num <= 26) {
            double_count = dp[idx + 2];
        }
        
        // count값은, idx번째 문자부터 끝까지 해당하는 문자열을 디코딩할 수 있는 방법의 수이다. -  (맨뒤 1개/나머지), (맨뒤 2개/나머지) 로 나누어서 각각의 
        // 디코딩 방법의 수를 더해서 완성한다. 
        int count = single_count + double_count;
        dp[idx] = count;
    }

    return dp[0];
}

int main() {
    string s;
    cout << "인코딩된 암호를 입력해 주세요! " << "\n";
    cin >> s;
    cout << "주어진 암호 " << s << " 를 디코딩하는 방법의 가짓수는 " << decodingBtmUp(s) <<  " 가지 입니다." << endl;
    return 0;
}

