#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

unordered_map<long long,long long> used;

long long find(long long roomNo) {
    if (used[roomNo] == 0) {
        used[roomNo] = roomNo+1;
        return roomNo;
    } 
    return used[roomNo] = find(used[roomNo]);
}

vector<long long> solution(long long k, vector<long long> room_number) {
    vector<long long> answer;
    for (int i = 0; i < room_number.size(); ++i) {
        long long roomNo = find(room_number[i]);
        answer.push_back(roomNo);
    }
    return answer;
}
