#include <string>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int solution(vector<int> food_times, long long k) {
    priority_queue<int, vector<int>, greater<int>> pq(food_times.begin(), food_times.end());

    int n = food_times.size();
    long long accDecTimes = 0, prevMinTimes = 0;
    while (!pq.empty()) {
        long long minTimes = pq.top();
        long long diff = (minTimes - prevMinTimes);
        long long delta = diff * n--;
        
        if (k-delta < 0) break;

        k -= delta;
        accDecTimes += diff;
        prevMinTimes = minTimes;
        pq.pop();
    }
    
    if (pq.empty()) return -1;

    vector<int> remainder;
    for (int i = 0; i < food_times.size(); ++i) {
        if (food_times[i] - accDecTimes <= 0) continue;
        remainder.push_back(i);
    }
    
    return remainder[k % remainder.size()] + 1;
}
