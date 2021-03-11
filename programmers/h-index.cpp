#include <string>
#include <vector>
#include <algorithm>

using namespace std;

bool decision(const vector<int>& citations, int h) {
    for (int i = 0; i < citations.size(); ++i) {
        if (citations[i] >= h && i+1 >= h) return true;
    }
    return false;
}

int solution(vector<int> citations) {
    sort(citations.begin(), citations.end(), greater<int>());
    int lo = 0, hi = 10000;
    while (lo <= hi) {
        int mid = lo + (hi-lo)/2;
        if (decision(citations, mid)) {
            lo = mid + 1;
        } else {
            hi = mid - 1;
        }
    }
    return lo - 1;
}
