#include <string>
#include <vector>

using namespace std;

int rangeSum(const vector<int>& psum, int a, int b) {
    if (a == 0) return psum[b];
    return psum[b] - psum[a-1];
}

int solution(vector<int> cookie) {
    int n = cookie.size();
    vector<int> psum(n,0);
    psum[0] = cookie[0];
    for (int i = 1; i < n; ++i) {
        psum[i] = psum[i-1] + cookie[i];
    }
    
    int ret = 0;
    for (int i = 0; i < n; ++i) {
        int start = 0, end = n-1;
        int leftRangeSum = rangeSum(psum, start, i);
        int rightRangeSum = rangeSum(psum, i+1, end);  
        while (start <= i && i < end) {        
            if (leftRangeSum < rightRangeSum) {
                rightRangeSum = rangeSum(psum, i+1, --end);
            } else if (leftRangeSum > rightRangeSum) {
                leftRangeSum = rangeSum(psum, ++start, i);
            } else {
                ret = max(ret, leftRangeSum);
                break;
            }
        }
    }
    return ret;
}
