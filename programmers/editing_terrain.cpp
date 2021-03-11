#include <vector>

using namespace std;

long long calcCost(const vector<vector<int>>& land, int height, int P, int Q) {
    long long cost = 0;
    for (int i = 0; i < land.size(); ++i) {
        for (int j = 0; j < land.size(); ++j) {
            if (height < land[i][j]) {
                cost += static_cast<long long>(Q) * (land[i][j] - height);
            } else if (height > land[i][j]) {
                cost += static_cast<long long>(P) * (height - land[i][j]);
            }
        }
    }
    return cost;
}

long long solution(vector<vector<int> > land, int P, int Q) {
    int lo = 0, hi = 1000000000;
    while (lo <= hi) {
        int mid = lo + (hi-lo)/2;
        long long r1 = calcCost(land, mid, P, Q), r2 = calcCost(land, mid+1, P, Q);
        if (r1 <= r2) {
            hi = mid-1;
        } else {
            lo = mid+1;
        }
    }
    return calcCost(land, hi+1, P, Q);
}
