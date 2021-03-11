#include <string>
#include <vector>
#include <cmath>

using namespace std;

int count(const string& members, int used, const vector<string>& data, string& perm) {
    if (used == (1<<members.size())-1) {  
        for (int i = 0; i < data.size(); ++i) {
            char first = data[i][0];
            char second = data[i][2];
            char op = data[i][3];
            int dist = data[i][4] - '0';

            auto firstIdx = perm.find(string(1,first));
            auto secondIdx = perm.find(string(1,second));
            if (firstIdx > secondIdx) swap(firstIdx, secondIdx);
            int diff = secondIdx-firstIdx-1;

            if (op == '>') {
                if (diff <= dist) return 0;
            } else if (op == '<') {
                if (diff >= dist) return 0;
            } else {
                if (diff != dist) return 0;
            }
        }
        return 1;
    }

    int ret = 0;
    for (int i = 0; i < members.size(); ++i) {
        if (used & (1<<i)) continue;
        perm.push_back(members[i]);
        ret += count(members, used | (1<<i), data, perm);
        perm.pop_back();
    }
    return ret;
}

// 전역 변수를 정의할 경우 함수 내에 초기화 코드를 꼭 작성해주세요.
int solution(int n, vector<string> data) {
    string members{"ACFJMNRT"};
    string perm;
    return count(members, 0, data, perm);
}
