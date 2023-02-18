// 부분집합의 합 문제 - 동적 계획법 이용
// 1. 전수 조사 방식으로 부분집합의 합 문제 풀기
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void GetAllSubsets(vector<int> set, vector<int> subset, int index, vector<vector<vector<int>>>& allSubsets) { // 재귀를 이용해서 set의 모든 부분집합을 구하는 함수. 
    // 집합 set의 끝에 다다른 경우. 
    if (index == set.size()) {
        // 부분집합 크기를 인덱스로 활용하여 부분집합을 allSubsets에 추가. 
        allSubsets[subset.size()].emplace_back(subset);
        return;
    }

    // 원소를 추가하지 않고 재귀 호출
    GetAllSubsets(set, subset, index + 1, allSubsets);

    // 원소를 부분집합에 추가한 후 재귀 호출. 
    subset.emplace_back(set[index]);
    GetAllSubsets(set, subset, index + 1, allSubsets);
}

bool SubsetSum_BruteForce(vector<int> set, int target) {
    vector<vector<vector<int>>> allSubsets(set.size() + 1);
    GetAllSubsets(set, {}, 0, allSubsets);
    for (int size = 0; size <= set.size(); size++) {
        cout << "부분집합의 원소 개수 : " << size << endl;
        for (auto subset : allSubsets[size]) {
            cout << "\t{";

            int sum = 0;
            for (auto number : subset) {
                sum += number;
                cout << number << " ";
                cout << "} = " << sum << endl;

                if (sum == target) {
                    return true;
                }
            }
            return false;
        }
    }
}
int main() {
    vector<int> set = {13, 79, 45, 29};
    int target = 58;

    bool found = SubsetSum_BruteForce(set, target);
    if (found) {
        cout << "원소 합이 " << target < "인 부분집합이 있습니다. " << endl;
    } else {
        cout << "원소 합이 " << target < "인 부분집합이 없습니다. " << endl;
    }
}