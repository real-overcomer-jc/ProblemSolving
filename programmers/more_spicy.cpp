#include <string>
#include <vector>
#include <queue>

using namespace std;

int solution(vector<int> scoville, int K) {
    priority_queue<int, vector<int>, greater<int>> pq;
    for (auto& score : scoville) {
        pq.push(score);
    }
    
    int count = 0, op1 = 0, op2 = 0;
    while (pq.size() > 1 && pq.top() < K) {;
        op1 = pq.top(); pq.pop();
        op2 = pq.top(); pq.pop();
        pq.push(op1+op2*2);
        ++count;
    }
    return pq.top() < K ? -1 : count;
}
