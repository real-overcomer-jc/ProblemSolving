#include <string>
#include <vector>
#include <queue>

using namespace std;

int solution(vector<int> priorities, int location) {
    queue<pair<int,int>> q;
    for (int i = 0; i < priorities.size(); ++i) {
        q.push({priorities[i],i});
    }
    
    int count = 1;
    priority_queue<int> pq(priorities.begin(), priorities.end());
    while (!pq.empty()) {
        int max = pq.top(); pq.pop();
        while (q.front().first != max) {
            q.push(q.front());
            q.pop();
        }
        if (q.front().second == location) return count;
        q.pop();
        ++count;
    }
    return -1;
}
