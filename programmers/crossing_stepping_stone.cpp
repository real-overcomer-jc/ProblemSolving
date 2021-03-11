#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

bool decision(int mid, const vector<int>& stones, int k) {
    int count = 0;
    for (int i = 0; i < stones.size(); ++i) {
        if (stones[i] <= mid) ++count;
        else count = 0;
        if (count >= k) return true;
    }
    return false;
}

int solution(vector<int> stones, int k) {
    int lo = 1, hi = 200000000;
    while (lo <= hi) {
        int mid = (hi-lo)/2+lo;
        if (decision(mid, stones, k)) {
            //[mid,hi] 정답이 될 수 없는 구간
            hi = mid-1;
        } else {
            //[lo,mid] 정답이 될 수 있는 구간
            lo = mid+1;
        }
    }
    return hi+1;
}
