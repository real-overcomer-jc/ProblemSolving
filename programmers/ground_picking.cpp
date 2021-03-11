#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

int cache[100000][5];

int findMaxPath(const vector<vector<int>>& land, int n, int picked) {
    if (n == land.size()) return 0;
    
    int& ret = cache[n][picked];
    if (ret != -1) return ret;
    
    ret = 0;
    for (int i = 0; i < 4; ++i) {
        if (i == picked-1) continue;
        ret = max(ret, land[n][i] + findMaxPath(land, n+1, i+1));
    }
    return ret;
}

int solution(vector<vector<int> > land) {
    memset(cache, -1, sizeof cache);
    return findMaxPath(land, 0, 0);
}
