#include <string>
#include <vector>
#include <cstring>

using namespace std;

const int MOD = 1234567;

int cache[2001];

int count(int n) {
    if (n == 0) return 1;
    if (n < 0) return 0;
    
    int& ret = cache[n];
    if (ret != -1) return ret;
    
    return ret = (count(n-1) % MOD + count(n-2) % MOD) % MOD;
}

long long solution(int n) {
    memset(cache, -1, sizeof cache);
    return count(n);
}
