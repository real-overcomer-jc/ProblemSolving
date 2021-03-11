#include <string>
#include <vector>
#include <algorithm>

using namespace std;

long long solution(int n, vector<int> times) {
    sort(times.begin(), times.end());
    long long lo = 1;
    long long hi = n * times[times.size()-1];
    for (int iter = 0; iter < 100; ++iter) {
        long long mid = (hi-lo) / 2 + lo;
        long long processed = 0;
        for (auto& time : times) {
            processed += mid / time;
        }
        if (n <= processed) {
            hi = mid;
        } else {
            lo = mid;
        }
    }
    return hi;
}
