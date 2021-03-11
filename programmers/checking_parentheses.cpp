#include <string>
#include <vector>
#include <cstring>

using namespace std;

int cache[15][15];

int countParen(int nLeftParen, int nRightParen) {
    if (nLeftParen == 0 && nRightParen == 0) return 1;
    else if (nLeftParen < 0 || nRightParen < nLeftParen) return 0;
    
    int& ret = cache[nLeftParen][nRightParen];
    if (ret != -1) return ret;
    
    ret = countParen(nLeftParen-1, nRightParen);
    ret += countParen(nLeftParen, nRightParen-1);
    return ret;
}

int solution(int n) {
    memset(cache, -1, sizeof cache);
    return countParen(n,n);
}
