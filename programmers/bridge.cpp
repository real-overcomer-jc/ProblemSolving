#include <string>
#include <vector>
#include <algorithm>

using namespace std;

bool decision(const vector<int>& rocks, int dist, int n) {
    int prev = 0, removed = 0;
    for (int i = 0; i < rocks.size(); ++i) {
        if (rocks[i] - prev < dist) ++removed;
        else prev = rocks[i];
    }
    return removed > n;
}

int solution(int distance, vector<int> rocks, int n) {
    sort(rocks.begin(), rocks.end());
    rocks.push_back(distance);
    
    int lo = 1, hi = distance;
    while (lo <= hi) {
        int mid = lo + (hi-lo)/2;
        if (decision(rocks, mid, n)) {
            hi = mid-1;
        } else {
            lo = mid+1;
        }
    }
    return hi;
}
