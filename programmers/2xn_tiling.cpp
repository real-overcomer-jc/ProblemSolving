#include <string>
#include <vector>
#include <cstring>

using namespace std;

const int MOD = 1000000007;

int cache[60001];

int tiling(int n) {
    if (n <= 1) return 1;
    
    int& ret = cache[n];
    if (ret != -1) return ret;
    return ret = (tiling(n-1) + tiling(n-2)) % MOD;
}

int solution(int n) {
    memset(cache, -1, sizeof cache);
    return tiling(n);
}
