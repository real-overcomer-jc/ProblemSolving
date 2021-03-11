#include <vector>
#include <limits>

using namespace std;

const int INF = numeric_limits<int>::max();

int solution(vector<int> a) {
    const int n = a.size();
    vector<int> prefixMin(n), suffixMin(n);
    prefixMin[0] = a[0];
    for (int i = 1; i < n; ++i) {
        prefixMin[i] = min(prefixMin[i-1], a[i]);
    }
    
    suffixMin[n-1] = a[n-1];
    for (int i = n-2; i >= 0; --i) {
        suffixMin[i] = min(suffixMin[i+1], a[i]);
    }
    
    int ret = 0, leftMin, rightMin;
    for (int i = 0; i < n; ++i) {
        leftMin = (i > 0) ? prefixMin[i-1] : INF;
        rightMin = (i+1 < n) ? suffixMin[i+1] : INF;
        if (a[i] < leftMin || a[i] < rightMin) ++ret;
    }
    return ret;
}
