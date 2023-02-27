// word break - dp로 해결. 
// 문자열이 주어지고, 단어들의 집합이 주어진다. 그러면 단어들의 집합의 원소만으로 주어진 문자열을 구성할 수 있을까?
#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>

using namespace std;

// 문자열과, dict를 입력받아서, dict내 원소들만으로, 문자열을 구성할 수 있는지를 출력해주는 함수. 
bool wordBreak(string s, vector<string>& wordDict) {

    // wordDict에 사용하고자 하는 문자열이 존재하는지 아닌지만 파악하면 되므로 unordered_set 이용.
    unordered_set<string> word_set(wordDict.begin(), wordDict.end());
    int str_length = s.length();

    // dp_arry는, 0번 index는 빈 문자열, 그리고, i번째 index에는 문자열의 첫 번째 문자부터, i,번째 index의 문자까지의 문자열을 
    // wordDict 내의 단어로 구성할 수 있는지를 T/F로 저장하는 배열이다. 
    vector<bool> dp_arry(str_length + 1, false);

    // 빈 문자열은 언제나 만들 수 있으므로 true로 초기화한다. 
    dp_arry[0] = true;

    for (int idx = 1; idx <= str_length; ++idx) {

        // wordDict내의 단어들을 순회하며 살펴본다. 
        for (const string& word : word_set) {
            int word_length = word.length();

            // prev_idx는, 현재 index에서, 현재 wordDict내에서 참조하고 있는 단어의 길이만큼 뒤로 간 index이다. 
            int prev_idx = idx - word_length;

            // 만약 wordDict의 첫 번째 단어로 s의 첫 부분을 완성할 수 없다면, 넘어간다. wordDict를 어차피 모두 순회하게 되므로 걱정할 필요가 없다. 
            if (prev_idx < 0) continue;

            // 만약, prev_idx에 해당하는 dp_arry 값이 false인 경우, 이미 해당 위치까지의 문자열은 wordDict 내의 단어들로 만들 수 없으므로 false이다.
            if (!dp_arry[prev_idx]) continue;

            // 만약, prev_idx에 해당하는 dp_arry 값이 true인 경우, s.substr(prev_idx, word_length) == word 이면 wordDict내의 단어들로 구성할 수 있다. 
            if (s.substr(prev_idx, word_length) == word) {
                dp_arry[idx] = true;
                break;
            }
        }
    }
    return dp_arry[str_length];
}

int main() {
    int wordDict_length;
    string s;
    cout << "문자열을 입력해 주세요: " << "\n";
    cin >> s;
    vector<string> wordDict;
    cout << "이제 wordDict의 크기를 입력해 주세요!" << "\n";
    cin >> wordDict_length;
    cout << "이제 wordDict에 들어갈 내용들을 입력해 주세요 : " << "\n";
    for (int i = 0; i < wordDict_length; i++) {
        string word;
        cin >> word;
        wordDict.push_back(word);
    }

    // std::boolalpha의 사용 : bool 타입 변수를 true/false 로 출력해준다. 
    cout << std::boolalpha << wordBreak(s, wordDict) << endl;
    return 0;
}
