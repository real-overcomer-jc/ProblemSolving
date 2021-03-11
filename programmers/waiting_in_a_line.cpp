#include <string>
#include <vector>
#include <algorithm>

using namespace std;

long long factorial[21];

void prepare() {
    factorial[0] = factorial[1] = 1;
    for (int i = 2; i < 21; ++i) {
        factorial[i] = i * factorial[i-1];
    }
}

void permutate(const int n, long long skip, int used, vector<int>& perm) {
    if (n == perm.size()) return;
    
    long long quotient = skip / factorial[n-1-perm.size()];
    skip %= factorial[n-1-perm.size()];
    
    int i = 0;
    for (; i < n; ++i) {
        if (used & (1<<i)) continue;
        if (quotient == 0) break;
        --quotient;
    }
    perm.push_back(i+1);
    permutate(n, skip, used | (1<<i), perm);
}

vector<int> solution(int n, long long k) {
    prepare();
    vector<int> perm;
    permutate(n,k-1,0,perm);
    return perm;
}
